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

		void Gather(Camera& _Camera);

	private:
		// todo Octree or some BVH
		std::vector<RenderObject*> m_Objects;
	};
}// Tracy

#endif // !TRACY_SCENE_H
