///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class PrimitiveManager: public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PrimitiveManager  (const DeviceManagerPtr&);
    ~PrimitiveManager ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    PrimitivePtr        CreatePrimitive        ();
    PrimitivePtr        CreatePrimitive        (const PrimitiveBuffersPtr&);
    PrimitiveBuffersPtr CreatePrimitiveBuffers (MeshBufferUsage lines_usage = MeshBufferUsage_Stream, MeshBufferUsage sprites_usage = MeshBufferUsage_Stream);    
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������: �������� �� ������ ����������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static bool IsMeshLibraryResource (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� / �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LoadMeshLibrary   (const char* name);
    void LoadMeshLibrary   (const media::geometry::MeshLibrary&);
    void UnloadMeshLibrary (const char* name);
    void UnloadMeshLibrary (const media::geometry::MeshLibrary&);    
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PrimitiveProxy GetPrimitiveProxy (const char* name); //�������� ������ � ������ ����������
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PrimitivePtr FindPrimitive (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void         SetDefaultPrimitive (const PrimitivePtr& primitive);
    PrimitivePtr DefaultPrimitive    ();
  
  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};
