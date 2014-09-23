///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class EffectLoaderLibrary: public xtl::noncopyable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    template <class Ptr> class Library: public xtl::noncopyable
    {
      public:
        typedef Ptr Item;
      
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
        Library  ();
        ~Library ();
        
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
        size_t Size ();
        
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� / �������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
        void Add    (const char* id, const Item& item);
        void Remove (const char* id);
        void Clear  ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
        Item Find (const char* id); //return Item () if item not found
        
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
        typedef xtl::function<void (const char* id, Item&)> VisitFunction;
        
        void ForEach (const VisitFunction&);

      private:
        struct Impl;
        stl::auto_ptr<Impl> impl;
    };
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    EffectLoaderLibrary  ();
    ~EffectLoaderLibrary ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef Library<LowLevelRasterizerStatePtr>    RasterizerStateLibrary;
    typedef Library<LowLevelBlendStatePtr>         BlendStateLibrary;
    typedef Library<LowLevelDepthStencilStatePtr>  DepthStencilStateLibrary;
    typedef Library<LowLevelSamplerStatePtr>       SamplerStateLibrary;
    typedef Library<LowLevelTextureDescPtr>        TextureDescLibrary;    
    typedef Library<ProgramPtr>                    ProgramLibrary;
    typedef Library<EffectPassPtr>                 EffectPassLibrary;
    typedef Library<EffectPtr>                     EffectLibrary;    
    
    RasterizerStateLibrary&    RasterizerStates        ();
    RasterizerStateLibrary&    RasterizerScissorStates ();    
    BlendStateLibrary&         BlendStates             ();
    DepthStencilStateLibrary&  DepthStencilStates      ();
    SamplerStateLibrary&       SamplerStates           ();
    TextureDescLibrary&        TextureDescs            ();
    ProgramLibrary&            Programs                ();
    media::rfx::ShaderLibrary& Shaders                 ();
    EffectPassLibrary&         EffectPasses            ();
    EffectLibrary&             Effects                 ();
    
  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
void parse_effect_library (const DeviceManagerPtr&, const TextureManagerPtr&, const common::ParseNode& node, const char* file_name, EffectLoaderLibrary& library);
