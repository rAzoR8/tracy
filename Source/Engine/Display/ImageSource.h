#ifndef TRACY_IMAGESOURCE_H
#define TRACY_IMAGESOURCE_H

#include <vector>
#include "HashUtils.h"
#include "UniqueAssociationID.h"
#include "Logger.h"
#include "Texture.h"

namespace Tracy
{
	class ImageSource
	{
	public:
		ImageSource() {};
		virtual ~ImageSource() {};

		struct Image
		{
			Image(const uint64_t& _uHash = 0u, const Texture& _Img = nullptr) :
				uHash(_uHash), Img(_Img){}
			uint64_t uHash;
			Texture Img;

			bool operator<(const Image& _Other) const { return uHash < _Other.uHash; }
		};

		void AddImage(const Texture& _Img, const uint64_t _uNameHash);
		void AddImage(Texture&& _Img, const uint64_t _uNameHash);

		// call after the last image has been added
		void Finalize();

		const uint32_t& GetID() const;

		const std::vector<Image>& GetImages() const;

		static size_t GetInstanceCount();

	private:
		uint32_t m_uID = HUNDEFINED32;
		std::vector<Image> m_Images;

		// map hash to linear id
		static hlx::UniqueAssociationID<uint64_t, uint32_t> m_SrcIds;
	};

	inline void ImageSource::AddImage(const Texture& _Img, const uint64_t _uNameHash)
	{
		m_Images.emplace_back(_uNameHash, _Img);
	}

	inline void ImageSource::AddImage(Texture&& _Img, const uint64_t _uNameHash)
	{
		m_Images.emplace_back(_uNameHash, std::move(_Img));
	}

	inline void ImageSource::Finalize()
	{
		HASSERT(m_uID == HUNDEFINED32, "ImageSources has already been initialized with id %u", m_uID);

		std::sort(m_Images.begin(), m_Images.end());

		uint64_t uHash = 0u;
		for (const Image& img : m_Images)
		{
			uHash = hlx::CombineHashes(uHash, img.uHash);
		}

		m_uID = m_SrcIds.GetAssociatedID(uHash);
	}

	inline const uint32_t& ImageSource::GetID() const
	{
		return m_uID;
	}

	inline const std::vector<ImageSource::Image>& ImageSource::GetImages() const
	{
		return m_Images;
	}

	inline size_t ImageSource::GetInstanceCount() { return m_SrcIds.GetAssociationCount(); }

} // Tracy

#endif // !TRACY_IMAGESOURCE_H
