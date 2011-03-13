///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class TextureImpl: public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TextureImpl  (const DeviceManagerPtr& manager,
                  TextureDimension        dimension,
                  size_t                  width,
                  size_t                  height,
                  size_t                  depth,
                  PixelFormat             format,
                  bool                    generate_mipmaps);
    ~TextureImpl ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    LowLevelTexturePtr DeviceTexture ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TextureDimension Dimension ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PixelFormat Format ();
    size_t      Width  ();
    size_t      Height ();
    size_t      Depth  ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderTargetPtr RenderTarget (size_t layer, size_t mip_level);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Update (const media::Image&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Capture (size_t layer, size_t mip_level, media::Image& image);
    void Capture (size_t mip_level, media::Image& image);
    
  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};
