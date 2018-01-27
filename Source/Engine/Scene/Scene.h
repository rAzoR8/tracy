#ifndef TRACY_SCENE_H
#define TRACY_SCENE_H

#include <vector>

namespace Tracy
{
	class Camera;
	class RenderObject;

	struct SceneDesc
	{
	
	};

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		bool Initialize(const SceneDesc& _Desc);

		void Update();

		void Gather(Camera& _Camera);

	private:
		void UpdateTransforms(const bool _bSkipStaticTransforms = true);

		void AddObject(RenderObject* _pObject, Camera& _Camera, const bool _bAddChildObjects = true);

	private:
		// todo Octree or some BVH
		std::vector<RenderObject*> m_Objects;
	};
}// Tracy

#endif // !TRACY_SCENE_H
