///forward declarations
class PrimitiveBuffersImpl;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���
///////////////////////////////////////////////////////////////////////////////////////////////////
class PrimitiveImpl: public Object, public CacheSource
{
  public:
    typedef xtl::intrusive_ptr<PrimitiveBuffersImpl> BuffersPtr;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PrimitiveImpl  (const DeviceManagerPtr&, const MaterialManagerPtr&, const BuffersPtr& buffers, const char* name = "");
    ~PrimitiveImpl ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name    ();
    void        SetName (const char* id);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const BuffersPtr& Buffers ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t MeshesCount     ();
    size_t AddMesh         (const media::geometry::Mesh&, MeshBufferUsage vb_usage, MeshBufferUsage ib_usage);
    void   RemoveMeshes    (size_t first_mesh, size_t meshes_count);
    void   RemoveAllMeshes ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t                 SpriteListsCount                 ();
    BillboardSpriteListPtr AddStandaloneBillboardSpriteList (const math::vec3f& up, MeshBufferUsage vb_usage, MeshBufferUsage ib_usage);
    BillboardSpriteListPtr AddBatchingBillboardSpriteList   (const math::vec3f& up);
    OrientedSpriteListPtr  AddStandaloneOrientedSpriteList  (const math::vec3f& up, MeshBufferUsage vb_usage, MeshBufferUsage ib_usage);
    OrientedSpriteListPtr  AddBatchingOrientedSpriteList    (const math::vec3f& up);
    void                   RemoveSpriteList                 (const BillboardSpriteListPtr&);
    void                   RemoveSpriteList                 (const OrientedSpriteListPtr&);
    void                   RemoveAllSpriteLists             ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t      LineListsCount        ();
    LineListPtr AddStandaloneLineList (MeshBufferUsage vb_usage, MeshBufferUsage ib_usage);
    LineListPtr AddBatchingLineList   ();
    void        RemoveLineList        (const LineListPtr&);
    void        RemoveAllLineLists    ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t                  RendererPrimitiveGroupsCount ();
    RendererPrimitiveGroup* RendererPrimitiveGroups      ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void FillDynamicPrimitiveStorage (DynamicPrimitiveEntityStorage&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    using CacheSource::UpdateCache;
    using CacheSource::ResetCache;

  private:
    void AddDynamicPrimitiveList    (DynamicPrimitiveListImplBase*, int type);
    void RemoveDynamicPrimitiveList (DynamicPrimitiveListImplBase*);
      
  private:
    void UpdateCacheCore ();
    void ResetCacheCore ();
    
  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};
