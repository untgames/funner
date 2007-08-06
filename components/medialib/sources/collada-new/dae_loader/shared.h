#ifndef MEDIALIB_DAE_SHARED_HEADER
#define MEDIALIB_DAE_SHARED_HEADER

#include <media/collada/model.h>
#include <common/parser.h>
#include <xtl/functional>
#include <stl/hash_map>
#include <stl/vector>
#include <stl/string>
#include <math/io.h>

using namespace medialib::collada;
using namespace common;
using namespace xtl;
using namespace math;

namespace medialib
{

namespace collada
{

//forward declarations
class  DaeParser;
class  MeshSourceMap;
class  MeshInputBuilder;
struct SurfaceInfo;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ����� � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> struct String2Value
{
  const char* string; //��������� ��������
  T           value;  //��������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������, ����������� ����������� ���� ������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class LogScope
{
  public:
    LogScope  (Parser::Node* node, DaeParser& parser, const char* id = 0);
    ~LogScope ();

    Parser::Node* Node () const { return node; }
    LogScope*     Prev () const { return prev; }
    const char*   Id   () const { return id; }
  
  private:
    DaeParser&    parser;
    Parser::Node* node;
    LogScope*     prev;
    const char*   id;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class DaeParser
{
  friend class LogScope;
  typedef Model::LogFunction LogFunction;
  public:    
    DaeParser (const char* file_name, Model& model, const LogFunction& log);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LogError   (Parser::Node* node, const char* format, ...);
    void LogWarning (Parser::Node* node, const char* format, ...);    
    
  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������ � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void PrintLog (const LogFunction&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void ParseRoot                (Parser::Iterator);
    void ParseLibraries           (Parser::Iterator);
    void ParseLibraryEffects      (Parser::Iterator);
    void ParseLibraryMaterials    (Parser::Iterator);
    void ParseLibraryGeometries   (Parser::Iterator);
    void ParseLibraryControllers  (Parser::Iterator);
    void ParseLibraryLights       (Parser::Iterator);
    void ParseLibraryCameras      (Parser::Iterator);
    void ParseLibraryVisualScenes (Parser::Iterator);
    void ParseImage               (Parser::Iterator);
    void ParseEffect              (Parser::Iterator);
    void ParseEffectProfileCommon (Parser::Iterator, Effect& effect);
    bool ParseTexture             (Parser::Iterator, Parser::Iterator profile_iter, Texture& texture);
    void ParseMaterial            (Parser::Iterator);
    void ParseGeometry            (Parser::Iterator);
    void ParseMesh                (Parser::Iterator, Mesh& mesh);
    void ParseMeshSource          (Parser::Iterator, MeshSourceMap& sources);
    void ParseSurfaceInput        (Parser::Iterator, Parser::Iterator mesh_iter, MeshSourceMap& sources, MeshInputBuilder& inputs);
    void ParseSurface             (Parser::Iterator, Parser::Iterator mesh_iter, Mesh& mesh, PrimitiveType type, MeshSourceMap& sources);
    void ParseSurfaceBuffers      (Parser::Iterator, Parser::Iterator surface_iter, SurfaceInfo& info);
    void ParseController          (Parser::Iterator);
    void ParseMorph               (Parser::Iterator, const char* id);
    void ParseSkin                (Parser::Iterator, Skin& skin);
    void ParseLight               (Parser::Iterator);
    void ParseCamera              (Parser::Iterator);
    void ParseVisualScene         (Parser::Iterator);
    void ParseNode                (Parser::Iterator, Node& parent);
    bool ParseTransform           (Parser::Iterator, math::mat4f& tm);
    void ParseInstanceLight       (Parser::Iterator, Node::LightList& lights);
    void ParseInstanceCamera      (Parser::Iterator, Node::CameraList& cameras);
    void ParseInstanceGeometry    (Parser::Iterator, Node::MeshList& meshes);
    void ParseBindMaterial        (Parser::Iterator iter, MaterialBinds& binds);
    void ParseIdrefArray          (Parser::Iterator iter, stl::vector <stl::string> *source);
    void ParseFloatArray          (Parser::Iterator iter, stl::vector <float> *source);

  private:
    template <class T> bool CheckedRead (Parser::Node* node, const char* tag, T& value)
    {
      if (node && tag)
        node = node->First (tag);        

      if (!node)
        return false;
                    
      if (!read (node, 0, value))
      {
        const char* str_value = get<const char*> (node, 0);
        
        LogScope scope (node, *this);
        
        LogError (node, "Incorrect value '%s'", str_value ? str_value : "UNREADABLE");
        return false;
      }
      
      return true;
    }   

  private:
    Model&    model;         //����������� ������
    ParseLog  parse_log;     //�������� �������
    Parser    parser;        //������
    LogScope* current_scope; //������� ���� �������
};

}

}

#endif
