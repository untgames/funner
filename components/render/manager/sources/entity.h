struct RendererPrimitive;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct RendererOperation
{
  EntityImpl*                     entity;             //������
  render::low_level::IStateBlock* entity_state_block; //���� ��������� �������
  const RendererPrimitive*        primitive;          //��������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct RendererOperationList
{
  size_t                   operations_count; //���������� ��������
  const RendererOperation* operations;       //��������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class EntityImpl: public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    EntityImpl  (const DeviceManagerPtr&, const PrimitiveManagerPtr&);
    ~EntityImpl ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    DynamicTextureEntityStorage& DynamicTextureStorage ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                       SetProperties (const common::PropertyMap&);
    const common::PropertyMap& Properties    ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetTransformation (const math::mat4f&);
    const math::mat4f& Transformation    ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������� (��� ���������)
///  �������������� ���������� �� ������� Entity::Transformation � ������ ���� ��� �� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetJointsCount         (size_t count);
    size_t             JointsCount            ();
    void               SetJointTransformation (size_t joint_index, const math::mat4f&);
    const math::mat4f& JointTransformation    (size_t joint_index);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t LodsCount ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PrimitivePtr Primitive           (size_t level_of_detail);
    const char*  PrimitiveName       (size_t level_of_detail);  
    void         SetPrimitive        (const PrimitivePtr&, size_t level_of_detail);
    void         SetPrimitive        (const char* name, size_t level_of_detail);
    void         ResetPrimitive      (size_t level_of_detail);
    bool         HasPrimitive        (size_t level_of_detail);
    void         ResetAllPrimitives  ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const RendererOperationList& RendererOperations (size_t level_of_detail);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};
