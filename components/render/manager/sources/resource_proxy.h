///implementation forwards
template <class Ptr> class  ResourceProxyManager;
template <class Ptr> struct ResourceProxyManagerImpl;
template <class Ptr> struct ResourceProxyImpl;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������ ��� �������� ������ �� ����������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Ptr> class ResourceProxy
{
  friend class ResourceProxyManager<Ptr>;
  public:
    typedef Ptr                           Pointer;
    typedef ResourceProxyManager<Pointer> Manager;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ResourceProxy  (const ResourceProxy&);
    ~ResourceProxy ();

    ResourceProxy& operator = (const ResourceProxy&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� ������ ������ �������� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsDefaultResource ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Pointer     Resource    ();     
    void        SetResource (const Pointer&);
    const char* Name        ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �� ������� ���������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AttachCacheHolder (CacheHolder&);
    void DetachCacheHolder (CacheHolder&);

  private:
    typedef ResourceProxyManagerImpl<Ptr> ManagerImpl;
    typedef ResourceProxyImpl<Ptr>        Impl;    
  
    ResourceProxy (Impl*);
    ResourceProxy (ManagerImpl&, const char* name);
    
    void SetDefaultResource (const Pointer&);

  private:  
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ �������� ��� �������� ������ �� ����������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Ptr> class ResourceProxyManager: public xtl::noncopyable
{
  public:
    typedef Ptr                Pointer;
    typedef ResourceProxy<Ptr> Proxy;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ResourceProxyManager  ();
    ~ResourceProxyManager ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Proxy GetProxy (const char* name); //�������� ������, � ������ ����������
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    Pointer FindResource (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void    SetDefaultResource (const Pointer&);
    Pointer DefaultResource    ();    
  
  private:
    typedef ResourceProxyManagerImpl<Ptr> Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef ResourceProxy<TexturePtr>              TextureProxy;
typedef ResourceProxy<LowLevelSamplerStatePtr> SamplerProxy;
typedef ResourceProxy<PrimitivePtr>            PrimitiveProxy;
typedef ResourceProxy<MaterialPtr>             MaterialProxy;
typedef ResourceProxy<LowLevelProgramPtr>      ProgramProxy;
typedef TextureProxy::Manager                  TextureProxyManager;
typedef SamplerProxy::Manager                  SamplerProxyManager;
typedef PrimitiveProxy::Manager                PrimitiveProxyManager;
typedef MaterialProxy::Manager                 MaterialProxyManager;
typedef ProgramProxy::Manager                  ProgramProxyManager;
