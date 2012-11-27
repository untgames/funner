#include "shared.h"

using namespace social;

const char* APP_ID = "271022146306708";

void log_print (const char* stream, const char* message)
{
  printf ("%s: %s\n", stream, message);
  fflush (stdout);
}

void dump (const common::PropertyMap& properties)
{
  printf ("    map has %u properties (hash=%08x, layout_hash=%08x):\n",
    properties.Size (), properties.Hash (), properties.LayoutHash ());

  for (size_t i=0, count=properties.Size (); i<count; i++)
  {
    stl::string value;

    properties.GetProperty (i, value);

    printf ("     #%u: name='%s', type=%s, value='%s'\n", i, properties.PropertyName (i), get_name (properties.PropertyType (i)), value.c_str ());
  }
}

void dump (const User& user)
{
  printf ("  id        '%s'\n", user.Id ());
  printf ("  nickname  '%s'\n", user.Nickname ());
  printf ("  is friend %c\n", user.IsFriend () ? 'y' : 'n');
  printf ("  handle    %d\n",   user.Handle ());
  printf ("  properties:\n");
  dump (user.Properties ());
}

void load_friends_callback (const UserList& users, OperationStatus status, const char* error)
{
  switch (status)
  {
    case social::OperationStatus_Success:
    {
      printf ("Load friends succeeded\n");

      printf ("Friends count %d:\n", users.Size ());

      for (size_t i = 0, count = users.Size (); i < count; i++)
      {
        printf ("  Friend %u:\n", i);
        dump (users [i]);
      }

      break;
    }
    case social::OperationStatus_Canceled:
      printf ("Load friends canceled\n");
      break;
    case social::OperationStatus_Failure:
      printf ("Load friends failed, error '%s'\n", error);
      break;
    default:
      printf ("Load friends status unknown\n");
  }
}

void load_user_callback (const User& user, OperationStatus status, const char* error)
{
  printf ("User details loaded:\n");
  dump (user);
}

void login_callback (social::OperationStatus status, const char* error, social::Session* session)
{
  switch (status)
  {
    case social::OperationStatus_Success:
    {
      printf ("Login succeeded\n");

      const social::User& user = session->CurrentUser ();

      printf ("Logged in user:\n");

      dump (user);

      common::PropertyMap properties;

      properties.SetProperty ("Fields", "first_name,last_name");

      session->LoadFriends (user, &load_friends_callback, properties);

      properties.SetProperty ("Fields", "first_name,last_name,picture,birthday,gender");

      session->LoadUser (user.Id (), &load_user_callback, properties);

      break;
    }
    case social::OperationStatus_Canceled:
      printf ("Login canceled\n");

      syslib::Application::Exit (0);
      break;
    case social::OperationStatus_Failure:
      printf ("Login failed, error '%s'\n", error);

      syslib::Application::Exit (0);
      break;
    default:
      printf ("Login status unknown\n");

      syslib::Application::Exit (0);
  }
}

int main ()
{
  printf ("Results of login_test:\n");

  try
  {
    common::LogFilter log_filter ("*", &log_print);

    syslib::Window parent_window (syslib::WindowStyle_Overlapped);

    parent_window.SetSize (800, 600);
    parent_window.SetPosition (100, 100);
    parent_window.Show ();

    social::Session session ("Facebook");
    
//    session.LogOut ();

    common::PropertyMap login_properties;

    login_properties.SetProperty ("AppId", APP_ID);
    login_properties.SetProperty ("Permissions", "user_birthday");

    session.LogIn (xtl::bind (&login_callback, _1, _2, &session), login_properties);

    syslib::Application::Run ();
  }
  catch (std::exception& exception)
  {
    printf ("exception: %s\n", exception.what ());
  }

  return 0;
}
