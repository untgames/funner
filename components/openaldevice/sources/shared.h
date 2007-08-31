#ifndef SOUND_SYSTEM_OPENAL_DEVICE_SHARED_HEADER
#define SOUND_SYSTEM_OPENAL_DEVICE_SHARED_HEADER

#include <stdarg.h>
#include <sound/openal_device.h>
#include <xtl/function.h>
#include <xtl/tuple>
#include <stl/string>
#include <common/strlib.h>
#include <common/exception.h>
#include <al.h>
#include <alc.h>

namespace sound
{

namespace low_level
{

struct OpenALExceptionTag;

typedef common::DerivedException<common::Exception, OpenALExceptionTag> OpenALException;

const float BUFFER_UPDATE_TIME = 0.5;

///////////////////////////////////////////////////////////////////////////////////////////////////
///C������ ��������������� �����, ������������� ����� OpenAL
///////////////////////////////////////////////////////////////////////////////////////////////////
struct OpenALDevice : public sound::low_level::ISoundDevice
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������/����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    OpenALDevice  (const char* device_name = NULL);
    ~OpenALDevice ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� �� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetCapabilities (Capabilities&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t ChannelsCount ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� �������������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetSample (size_t channel, const char* sample_name);
    const char* GetSample (size_t channel);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������� ������������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsLooped (size_t channel);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetSource (size_t channel, const Source&);
    void GetSource (size_t channel, Source&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void  Play  (size_t channel, bool looping = false);
    void  Pause (size_t channel);
    void  Stop  (size_t channel);
    void  Seek  (size_t channel, float time_in_seconds);
    float Tell  (size_t channel);
    bool  IsPlaying (size_t channel);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ ��������� ��� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void  SetVolume (float gain);
    float GetVolume ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetMute (bool state);
    bool IsMuted ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetListener (const Listener&);
    void GetListener (Listener&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ����������� ����������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void              SetDebugLog (const LogHandler&);
    const LogHandler& GetDebugLog ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddRef  ();
    void Release ();

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateBuffers ();

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� OpenAL
///////////////////////////////////////////////////////////////////////////////////////////////////
class OpenALContext
{
  public:
    typedef OpenALDevice::LogHandler LogHandler;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    OpenALContext  (const char* device_name, const LogHandler& log_handler);
    ~OpenALContext ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsCurrent   () const;
    bool MakeCurrent ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��� �������� OpenAL
///////////////////////////////////////////////////////////////////////////////////////////////////
     void alGenSources( ALsizei n, ALuint* sources );     
     void alDeleteSources( ALsizei n, const ALuint* sources );
     void alGetSourcef( ALuint sid, ALenum param, ALfloat* value );
     void alGetSource3f( ALuint sid, ALenum param, ALfloat* value1, ALfloat* value2, ALfloat* value3);
     void alGetSourcefv( ALuint sid, ALenum param, ALfloat* values );
     void alGetSourcei( ALuint sid,  ALenum param, ALint* value );
     void alGetSource3i( ALuint sid, ALenum param, ALint* value1, ALint* value2, ALint* value3);
     void alGetSourceiv( ALuint sid,  ALenum param, ALint* values );

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LogError (const char* message, ...);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� � OpenAL
///////////////////////////////////////////////////////////////////////////////////////////////////
    template <class Fn, class Tuple>
    void Dispatch (const char* function_name, Fn fn, const Tuple& args);

    template <class Ret, class Fn, class Tuple>
    Ret Dispatch (const char* function_name, Fn fn, const Tuple& args);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ ����� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    template <class Tuple>
    void CheckErrors (const char* function_name, const Tuple& args);

  private:
    OpenALContext (const OpenALContext&); //no impl
    OpenALContext& operator = (const OpenALContext&); //no impl

  private:
    ALCdevice*  device;       //���������� OpenAL
    ALCcontext* context;      //�������� OpenAL
    LogHandler  log_handler;  //������� ����������������
};


}

}

#endif
