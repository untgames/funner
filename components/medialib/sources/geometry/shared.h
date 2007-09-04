#ifndef MEDIALIB_GEOMETRY_SHARED_HEADER
#define MEDIALIB_GEOMETRY_SHARED_HEADER

#include <memory.h>
#include <float.h>

#include <stl/string>
#include <stl/vector>
#include <stl/hash_map>
#include <xtl/function.h>

#include <mathlib.h>
#include <common/strlib.h>
#include <common/hash.h>
#include <common/exception.h>

#include <media/geometry/mesh_model.h>
#include <shared/shared_resource.h>

namespace medialib
{

namespace geometry
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Buffer
{
  public:
    Buffer  ();
    Buffer  (size_t size);
    Buffer  (const Buffer&);
    ~Buffer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������ / ����� ������ (���������� ��������� ������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Size     () const { return finish - start; }
    size_t Capacity () const { return end_of_storage - start; }
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void* Data () { return start; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������ / �������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Resize  (size_t new_size);
    void Reserve (size_t new_size);
    
  private:
    Buffer& operator = (const Buffer&); //no impl
  
  private:      
    char *start, *finish, *end_of_storage;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� �������� ��������� � ��������������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
void copy (size_t vertices_count, const void* source, VertexAttributeType source_type, size_t source_stride,
           void* destination, VertexAttributeType destination_type, size_t destination_stride);
           
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������� ���-��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class MeshModelSystemImpl
{
  public:
    typedef MeshModelSystem::LoadFunction LoadFunction;
    typedef MeshModelSystem::SaveFunction SaveFunction;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    MeshModelSystemImpl ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ���������������� ������� �������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool RegisterLoader       (const char* extension, const LoadFunction& loader);
    bool RegisterSaver        (const char* extension, const SaveFunction& saver);
    void UnregisterLoader     (const char* extension);
    void UnregisterSaver      (const char* extension);
    void UnregisterAllLoaders ();
    void UnregisterAllSavers  ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� / ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Load (const char* file_name, MeshModel& model) const;
    void Save (const char* file_name, const MeshModel& model) const;

  private:
    typedef stl::hash_map<stl::hash_key<const char*>, LoadFunction> LoadFunctions;
    typedef stl::hash_map<stl::hash_key<const char*>, SaveFunction> SaveFunctions;
    
  private:
    LoadFunctions loaders;
    SaveFunctions savers;
};

typedef common::Singleton<MeshModelSystemImpl> MeshModelSystemSingleton;

}

}

#endif
