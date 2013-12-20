///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ���������� ���������� � �������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum SortMode
{
  SortMode_None,        //��� ����������
  SortMode_FrontToBack, //����������� �� �������� ��������� � ��������
  SortMode_BackToFront, //����������� �� �������� ��������� � ��������
  SortMode_StateSwitch, //������������ ��������� � ����� ���������� ���������� ������������ ���������
  
  SortMode_Default = SortMode_StateSwitch
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class EffectPass: public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    EffectPass  (const DeviceManagerPtr& device_manager);
    ~EffectPass ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                       SetColorTargets       (const common::StringArray& targets);
    void                       SetDepthStencilTarget (const char* name);
    const common::StringArray& ColorTargets          ();
    const char*                DepthStencilTarget    ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void   SetClearFlags (size_t clear_flags);
    size_t ClearFlags    ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                                SetBlendState             (const LowLevelBlendStatePtr&);
    void                                SetDepthStencilState      (const LowLevelDepthStencilStatePtr&);
    void                                SetRasterizerState        (const LowLevelRasterizerStatePtr&);
    void                                SetRasterizerScissorState (const LowLevelRasterizerStatePtr&);    
    const LowLevelBlendStatePtr&        BlendState                ();
    const LowLevelDepthStencilStatePtr& DepthStencilState         ();
    const LowLevelRasterizerStatePtr&   RasterizerState           ();
    const LowLevelRasterizerStatePtr&   RasterizerScissorState    ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    LowLevelStateBlockPtr StateBlock (bool scissor_enable);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ����������, ������� ������ � ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void          SetTags   (const char* tags);
    void          SetTags   (const common::StringArray& tags);    
    size_t        TagsCount ();
    const char*   Tag       (size_t index);
    size_t        TagHash   (size_t index);
    const char**  Tags      ();
    const size_t* TagHashes ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                      SetSortMode (render::manager::SortMode mode);
    render::manager::SortMode SortMode    ();

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class InstantiatedEffect: public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InstantiatedEffect  ();
    ~InstantiatedEffect ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void          SetTags   (const char* tags);
    void          SetTags   (const common::StringArray& tags);
    size_t        TagsCount ();
    const char*   Tag       (size_t index);
    size_t        TagHash   (size_t index);
    const char**  Tags      ();
    const size_t* TagHashes ();

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Effect: public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Effect  ();
    ~Effect ();    
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ������: ������������ ��� ������������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void          SetTags   (const char* tags);
    void          SetTags   (const common::StringArray& tags);
    size_t        TagsCount ();
    const char*   Tag       (size_t index);
    size_t        TagHash   (size_t index);
    const char**  Tags      ();
    const size_t* TagHashes ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������� / ��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t                OperationsCount     ();
    size_t                AddOperation        (const EffectPassPtr&); //returns order number of operation in rendering sequence
    size_t                AddOperation        (const InstantiatedEffectPtr&);    //returns order number of operation in rendering sequence
    EffectPassPtr         OperationPass       (size_t order_number);
    InstantiatedEffectPtr OperationEffect     (size_t order_number);
    void                  RemoveOperation     (size_t order_number);
    void                  RemoveAllOperations ();

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class EffectRenderer: public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    EffectRenderer  (const EffectPtr& effect, const DeviceManagerPtr& device_manager, FrameImpl& frame, ProgramParametersLayout* parent_layout = 0);
    ~EffectRenderer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� � ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddOperations (const RendererOperationList& operations,
                        size_t                       eye_distance,
                        const math::mat4f&           mvp_matrix,
                        render::low_level::IBuffer*  property_buffer = 0,
                        ProgramParametersLayout*     property_layour= 0);
    void AddOperations (FrameImpl& frame);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RemoveAllOperations ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void ExecuteOperations (RenderingContext& context);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};
