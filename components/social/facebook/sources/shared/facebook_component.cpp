#include "shared.h"

using namespace social;
using namespace social::facebook;

namespace
{

const char* COMPONENT_NAME    = "social.sessions.facebook"; //��� ����������
const char* SESSION_ID        = "Facebook";                 //������������� ������
const char* SESSION_NAME_MASK = "Facebook";                 //����� ���� ������

}

/*
   ��������� ������
*/

namespace components
{

namespace facebook
{

class FacebookComponent
{
  public:
    FacebookComponent ()
    {
      SessionManager::RegisterSession (SESSION_ID, SESSION_NAME_MASK, xtl::bind (&FacebookComponent::CreateSession, this, _1));
    }

  private:
    ISessionManager* CreateSession (const char* session_name)
    {
      static const char* METHOD_NAME = "social::facebook::FacebookComponent::CreateSession";

      if (xtl::xstrcmp (session_name, SESSION_NAME_MASK))
        throw xtl::make_argument_exception (METHOD_NAME, "session_name", session_name);

      return new FacebookSessionImpl ();
    }
};

extern "C"
{

common::ComponentRegistrator<FacebookComponent> FacebookSession (COMPONENT_NAME);

}

}

}

