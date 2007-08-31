#include <sound/device.h>
#include <common/exception.h>
#include <xtl/function.h>
#include <stdio.h>

using namespace sound::low_level;
using namespace common;

ISoundDevice* my_create_device (const char* driver_name, const char* device_name, const char* init_string)
{
  Raise<Exception> ("my_create_device", "Attempt to create sound device: driver='%s' device='%s' init_string='%s'",
                    driver_name, device_name, init_string);

  return 0;
}

int main ()
{
  printf ("Results of device1_test:\n");
  
  try
  {
    SoundSystem::RegisterDriver ("test_driver1", &my_create_device);
    SoundSystem::RegisterDriver ("test_driver2", &my_create_device);
    SoundSystem::RegisterConfiguration  ("test_driver1", "configuration1");
    SoundSystem::RegisterConfiguration  ("test_driver2", "configuration2");
    SoundSystem::RegisterConfiguration  ("test_driver1", "configuration3");
    
    printf ("configurations:\n");
    
    for (size_t i=0; i<SoundSystem::GetConfigurationsCount (); i++)
      printf ("  %s\n", SoundSystem::GetConfiguration (i));

    SoundSystem::CreateDevice (SoundSystem::FindConfiguration ("*", "*3"), "0");
  }
  catch (std::exception& exception)
  {
    printf ("Exception: %s\n", exception.what ());
  }

  return 0;
}
