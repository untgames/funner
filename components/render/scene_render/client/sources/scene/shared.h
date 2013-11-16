#ifndef RENDER_SCENE_CLIENT_IMPL_SCENE_SHARED_HEADER
#define RENDER_SCENE_CLIENT_IMPL_SCENE_SHARED_HEADER

#include <stl/hash_map>

#include <xtl/bind.h>
#include <xtl/common_exceptions.h>
#include <xtl/function.h>

#include <common/property_map.h>
#include <common/strlib.h>

#include <sg/scissor.h>

#include <shared/client.h>
#include <shared/entity.h>
#include <shared/scene_manager.h>
#include <shared/visual_model.h>

namespace render
{

namespace scene
{

namespace client
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class SceneFactory
{
  public:
    static Node* Create (scene_graph::Node& src_node, SceneManager& scene_manager);
};

}

}

}

#endif
