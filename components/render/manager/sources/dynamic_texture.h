///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class DynamicTextureImpl: public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    DynamicTextureImpl  (const char* name, Entity& entity, const RenderManager::DynamicTextureCreator& creator);
    ~DynamicTextureImpl ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TexturePtr Texture ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Update (const FramePtr& frame);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

