#ifndef RENDER_DX11_DRIVER_QUERY_MANAGER_SHARED_HEADER
#define RENDER_DX11_DRIVER_QUERY_MANAGER_SHARED_HEADER

#include <render/low_level/utils.h>

#include <shared/error.h>
#include <shared/query_manager.h>

namespace render
{

namespace low_level
{

namespace dx11
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Query: virtual public IPredicate, public DeviceObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Query  (const DeviceManager&, QueryType type);
    ~Query ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    QueryType GetType () { return type; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Begin (IDeviceContext* context);
    void End   (IDeviceContext* context);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////  
    void GetData    (size_t size, void* data, IDeviceContext* context);
    bool TryGetData (size_t size, void* data, IDeviceContext* context);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ID3D11Asynchronous& GetHandle () { return *query; }

  private:
    bool GetDataCore (size_t size, void* data, IDeviceContext* context, UINT flags);

  private:
    QueryType  type;  //��� �������    
    DxQueryPtr query; //������
};

typedef xtl::com_ptr<Query> QueryPtr;

}

}

}

#endif