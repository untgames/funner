///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ShaderCode: public DeviceObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ShaderCode  (const DeviceManager& device_manager,
                 const char*          name,
                 const char*          profile,
                 const char*          source_code,
                 size_t               source_code_length = (size_t)-1,
                 const char*          options = "",
                 const LogFunction&   log_fn = LogFunction (),
                 size_t               flags1 = 0,
                 size_t               flags2 = 0);
    ~ShaderCode ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const void* GetCompiledData     () const;
    size_t      GetCompiledDataSize () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetCompiledDataHash () const;

  private:
    DxBlobPtr data; //������ ������ �������
    size_t    hash; //���
};

typedef xtl::com_ptr<ShaderCode> ShaderCodePtr;