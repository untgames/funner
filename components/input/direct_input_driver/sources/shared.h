#ifndef INPUT_LOW_LEVEL_DIRECT_INPUT_DRIVER_SHARED_HEADER
#define INPUT_LOW_LEVEL_DIRECT_INPUT_DRIVER_SHARED_HEADER

#include <stl/hash_map>
#include <stl/string>
#include <stl/vector>

#include <xtl/bind.h>
#include <xtl/connection.h>
#include <xtl/common_exceptions.h>
#include <xtl/function.h>
#include <xtl/intrusive_ptr.h>
#include <xtl/reference_counter.h>
#include <xtl/shared_ptr.h>

#include <common/singleton.h>

#include <syslib/timer.h>
#include <syslib/window.h>

#include <input/low_level/device.h>
#include <input/low_level/driver.h>
#include <input/low_level/direct_input_driver.h>

#define DIRECTINPUT_VERSION 0x0800

#include <Dinput.h>

#pragma pack (1)

namespace input
{

namespace low_level
{

namespace direct_input_driver
{

enum ObjectType
{
  ObjectType_AbsoluteAxis,
  ObjectType_RelativeAxis,
  ObjectType_Button,
  ObjectType_POV,
  ObjectType_Unknown
};

/*class GameControlDevice: virtual public input::low_level::IDevice, public xtl::reference_counter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������/����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    GameControlDevice (syslib::Window* window, const char* name, IDirectInputDevice8* direct_input_device_interface);
    ~GameControlDevice ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetName () { return name.c_str (); }

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetEventHandler (const input::low_level::IDevice::EventHandler& handler)
    {
      event_handler = handler;
    }
    const input::low_level::IDevice::EventHandler& GetEventHandler ()
    {
      return event_handler;
    }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetProperties () {return "";}
    void        SetProperty   (const char* name, float value) {}
    float       GetProperty   (const char* name) {return 0.f;}
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddRef () { addref (this); }  
    void Release () { release (this); }

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void PollDevice ();

  private:
    GameControlDevice (const GameControlDevice& source);             //no impl
    GameControlDevice& operator = (const GameControlDevice& source); //no impl
    GameControlDevice ();                                            //no impl

  private:
    typedef xtl::com_ptr<IDirectInputDevice8> DirectInputDeviceInterfacePtr;

  private:
    stl::string                             name;
    DirectInputDeviceInterfacePtr           device_interface;
    input::low_level::IDevice::EventHandler event_handler;
    syslib::Timer                           poll_timer;
    DIJOYSTATE                              current_joy_state;
};*/

class OtherDevice: virtual public input::low_level::IDevice, public xtl::reference_counter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������/����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    OtherDevice (syslib::Window* window, const char* name, IDirectInputDevice8* direct_input_device_interface);
    ~OtherDevice ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetName () { return name.c_str (); }

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetEventHandler (const input::low_level::IDevice::EventHandler& handler)
    {
      event_handler = handler;
    }
    const input::low_level::IDevice::EventHandler& GetEventHandler ()
    {
      return event_handler;
    }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetProperties () { return properties.c_str (); }
    void        SetProperty   (const char* name, float value);
    float       GetProperty   (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddRef () { addref (this); }  
    void Release () { release (this); }

  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RegisterObject (const char* name, size_t offset, ObjectType type);

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void PollDevice ();

  private:
    OtherDevice (const OtherDevice& source);             //no impl
    OtherDevice& operator = (const OtherDevice& source); //no impl
    OtherDevice ();                                      //no impl

  private:
    enum ObjectPropertyType
    {
      ObjectPropertyType_Sensitivity,
      ObjectPropertyType_DeadZone,
      ObjectPropertyType_Saturation,

      ObjectPropertyType_Num
    };

    typedef stl::hash_map<stl::hash_key<const char*>, float> ObjectPropertyMap;

    struct ObjectData
    {
      stl::string                 name;
      size_t                      offset;
      ObjectType                  type;
      size_t                      min_value;                          //����������� �������� (��� �������� ���� ���)
      size_t                      max_value;                          //������������ �������� (��� �������� ���� ���)
      bool                        bad_object;                         //true ��� ������� ���� ���, ���� ������ �������� ������� ��������
      ObjectPropertyMap::iterator properties[ObjectPropertyType_Num]; //��������

      ObjectData () {}
      ObjectData (const char* in_name, size_t in_offset, ObjectType in_type) 
        : name (in_name), offset (in_offset), type (in_type), min_value (-65536), max_value (65535), bad_object (0)
        {}
    };

  private:
    typedef xtl::com_ptr<IDirectInputDevice8> DirectInputDeviceInterfacePtr;
    typedef stl::vector<ObjectData>           ObjectsArray;
    typedef xtl::uninitialized_storage<char>  DeviceDataBuffer;

  private:
    stl::string                             name;
    DirectInputDeviceInterfacePtr           device_interface;
    input::low_level::IDevice::EventHandler event_handler;
    syslib::Timer                           poll_timer;
    ObjectsArray                            objects;
    DeviceDataBuffer                        last_device_data;
    DeviceDataBuffer                        current_device_data;
    bool                                    device_lost;
    ObjectPropertyMap                       objects_properties_map;
    stl::string                             properties;
};

const char* get_direct_input_error_name (HRESULT error);

}

}

}

#endif
