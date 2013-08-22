#include <stl/auto_ptr.h>

#include <xtl/bind.h>
#include <xtl/common_exceptions.h>
#include <xtl/function.h>
#include <xtl/intrusive_ptr.h>
#include <xtl/reference_counter.h>
#include <xtl/trackable_ptr.h>

#include <common/property_map.h>
#include <common/strlib.h>
#include <common/time.h>

#include <syslib/condition.h>

#include <render/scene_render_client.h>

#include <render/scene/interchange/command_queue.h>
#include <render/scene/interchange/connection_manager.h>
#include <render/scene/interchange/context.h>
#include <render/scene/interchange/serializer.h>

namespace render
{

namespace scene
{

namespace client
{

typedef interchange::Context<interchange::ClientToServerSerializer, interchange::ServerToClientDeserializer> Context;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class ClientImpl: public xtl::noncopyable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ClientImpl  ();
    ~ClientImpl ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Dummy ();

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Connection: public xtl::noncopyable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Connection  (const char* connection_name, const char* init_string, size_t logon_timeout_ms);
    ~Connection ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Description ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    ClientImpl& Client ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    client::Context& Context ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void WaitServerFeedback    ();
    bool TryWaitServerFeedback (size_t timeout_ms);

  private:
    struct Impl;
    Impl* impl;  
};

}

}

}
