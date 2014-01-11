///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class MaterialManager: public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    MaterialManager  (const DeviceManagerPtr&, const TextureManagerPtr&, const ProgramManagerPtr&);
    ~MaterialManager ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    MaterialPtr CreateMaterial ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������: �������� �� ������ ����������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static bool IsMaterialLibraryResource (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� / �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LoadMaterialLibrary   (const char* name);
    void LoadMaterialLibrary   (const media::rfx::MaterialLibrary&);
    void UnloadMaterialLibrary (const char* name);
    void UnloadMaterialLibrary (const media::rfx::MaterialLibrary&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ��������� ������������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void ShareMaterial   (const char* name, const MaterialPtr& material);
    void UnshareMaterial (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    MaterialProxy GetMaterialProxy (const char* name); //�������� ������ � ������ ����������
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    MaterialPtr FindMaterial (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetDefaultMaterial (const MaterialPtr& material);
    MaterialPtr DefaultMaterial    ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �� �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    manager::DeviceManager& DeviceManager ();
  
  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};
