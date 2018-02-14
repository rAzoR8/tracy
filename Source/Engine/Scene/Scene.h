#ifndef TRACY_SCENE_H
#define TRACY_SCENE_H

#include "SceneDescription.h"
#include <memory>
#include "Datastructures/SmallObjectPool.h"

namespace Tracy
{
	class Camera;
	class RenderObject;
	
	class Scene
	{
		using TObjAllocator = SmallObjectPool<RenderObject, true, true>;
	public:
		inline static Scene& Instance()
		{
			static Scene GlobalScene{};
			return GlobalScene;
		}
		
		virtual ~Scene();

		bool Initialize(const SceneDesc& _Desc, const THandle _hDevice = 0u);

		void Update(const bool _bGatherCameras = true);

		void Gather(Camera& _Camera) const;

		void AddCamera(const std::shared_ptr<Camera>& _pCamera);

		const std::vector<std::shared_ptr<Camera>>& GetCameras() const;

	private:
		Scene();

		void FreeObjects();

		void UpdateTransforms(const bool _bSkipStaticTransforms = true);

		void AddObject(RenderObject* _pObject, Camera& _Camera, const bool _bAddChildObjects = true) const;

	private:
		std::unique_ptr<TObjAllocator> m_pObjectAllocator = nullptr;

		// todo Octree or some BVH
		std::vector<RenderObject*> m_Objects;

		std::vector<std::shared_ptr<Camera>> m_Cameras;
	};

	inline const std::vector<std::shared_ptr<Camera>>& Scene::GetCameras() const
	{
		return m_Cameras;
	}
}// Tracy

#endif // !TRACY_SCENE_H
