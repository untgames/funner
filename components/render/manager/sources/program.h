///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
struct TexmapDesc
{
  size_t      channel;    //����� ����������� ������
  stl::string semantic;   //��� ��������� � media::rfx::Texmap
  stl::string param_name; //��� ��������� � �������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Program: public Object, public CacheSource
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Program  (const char* name, const char* static_options, const char* dynamic_options);
    ~Program ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Attach           (const media::rfx::Shader&);
    void Detach           (const media::rfx::Shader&);
    void DetachAllShaders ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* StaticOptions  ();
    const char* DynamicOptions ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ��������� ���������� ����� �� ����� ������ � ��� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t            TexmapsCount     ();
    const TexmapDesc* Texmaps          ();
    const TexmapDesc& Texmap           (size_t index);
    void              SetTexmap        (size_t index, size_t channel, const char* semantic, const char* param_name);
    size_t            AddTexmap        (size_t channel, const char* semantic, const char* param_name);    
    void              RemoveTexmap     (size_t index);
    void              RemoveAllTexmaps ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Program& DerivedProgram (const ShaderOptions&);
    Program& DerivedProgram (ShaderOptionsCache&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������������� ��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const LowLevelProgramPtr& LowLevelProgram (render::low_level::IDevice&);
    
  private:
    Program (Program& parent, const ShaderOptions&);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};
