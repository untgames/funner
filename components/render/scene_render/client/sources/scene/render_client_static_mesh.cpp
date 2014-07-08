#include "shared.h"

using namespace render::scene;
using namespace render::scene::client;

namespace
{

///����������� ���
class StaticMesh: public VisualModel
{
  public:
///�����������
    StaticMesh (scene_graph::StaticMesh& mesh, SceneManager& manager)
      : VisualModel (mesh, manager, interchange::NodeType_StaticMesh)
      , mesh_name_hash () 
    {
    }

///�������� ����
    scene_graph::StaticMesh& SourceNode () const { return static_cast<scene_graph::StaticMesh&> (Node::SourceNode ()); }

  protected:
///���������� �������������
    void UpdateCore (client::Context& context)
    {
      try
      {
        VisualModel::UpdateCore (context);

        scene_graph::StaticMesh& mesh = SourceNode ();

          //������������� ����� ����

        size_t cur_mesh_name_hash = mesh.MeshNameHash ();

        if (cur_mesh_name_hash != mesh_name_hash)
        {
          context.SetStaticMeshName (Id (), mesh.MeshName ());

          mesh_name_hash = cur_mesh_name_hash;
        }    
      }
      catch (xtl::exception& e)
      {
        e.touch ("render::scene::client::StaticMesh::UpdateCore");
        throw;
      }
    }

  private:
    size_t mesh_name_hash; //��� ����� ����
};

}

namespace render {
namespace scene {
namespace client {

Node* create_node (scene_graph::StaticMesh& mesh, SceneManager& scene_manager)
{
  return new StaticMesh (mesh, scene_manager);
}

}}}