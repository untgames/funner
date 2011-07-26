///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class TextureManager: public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TextureManager  (const DeviceManagerPtr&);
    ~TextureManager ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    TexturePtr CreateTexture (const media::Image& image, bool generate_mipmaps, const char* name = "");
    TexturePtr CreateTexture (const media::Image& image, TextureDimension dimension, bool generate_mipmaps, const char* name = "");
    TexturePtr CreateTexture (const media::CompressedImage& image, const char* name = "");
    TexturePtr CreateTexture (const media::CompressedImage& image, TextureDimension dimension, const char* name = "");
    TexturePtr CreateTexture (TextureDimension dimension, size_t width, size_t height, size_t depth, PixelFormat format, bool generate_mipmaps, const char* name = "");
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������: �������� �� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static bool IsTextureResource (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� / �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LoadTexture   (const char* name);
    void ShareTexture  (const char* name, const TexturePtr& texture);    
    void UnloadTexture (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TextureProxy GetTextureProxy (const char* name); //�������� ������ � ������ ����������
    SamplerProxy GetSamplerProxy (const char* name); //�������� ������ � ������ ����������
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����������� �������� / ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TexturePtr              FindTexture (const char* name);
    LowLevelSamplerStatePtr FindSampler (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    DynamicTexturePtr CreateDynamicTexture (const char* name, EntityImpl& entity);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef RenderManager::DynamicTextureCreator DynamicTextureCreator;

    void RegisterDynamicTexture       (const char* name_mask, const DynamicTextureCreator& creator);
    void UnregisterDynamicTexture     (const char* name_mask);
    void UnregisterAllDynamicTextures ();
    bool IsDynamicTexture             (const char* name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� �� ��������� / �������� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                    SetDefaultTexture (const TexturePtr& texture);
    void                    SetDefaultSampler (const LowLevelSamplerStatePtr& sampler);
    TexturePtr              DefaultTexture    ();
    LowLevelSamplerStatePtr DefaultSampler    ();
  
  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};
