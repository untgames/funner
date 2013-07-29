#ifndef RENDER_SCENE_INTERCHANGE_CONNECTION_MANAGER_HEADER
#define RENDER_SCENE_INTERCHANGE_CONNECTION_MANAGER_HEADER

#include <xtl/functional_fwd>

#include <render/scene/interchange/connection.h>

namespace render
{

namespace scene
{

namespace interchange
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ConnectionManager
{
  public:
    typedef xtl::function<IConnection* (const char* name, const char* init_string)> ConnectionCreator;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������� �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void RegisterConnection       (const char* manager_name, const char* mask, const ConnectionCreator& creator);
    static void UnregisterConnection     (const char* manager_name);
    static void UrnegisterAllConnections ();
};

}

}

}

#endif
