#ifndef HSSERVER_CONNECTION_HEADER
#define HSSERVER_CONNECTION_HEADER

#include <cstddef>

namespace plarium
{

namespace hsserver
{

//forward declaration
class HsConnection;

///////////////////////////////////////////////////////////////////////////////////////////////////
///HS Connection states
///////////////////////////////////////////////////////////////////////////////////////////////////
enum HsConnectionState
{
  HsConnectionState_Disconnected,
  HsConnectionState_Connecting,
  HsConnectionState_Connected
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///HS Connection errors
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ErrorCode
{
  ErrorCode_Generic,
  ErrorCode_SendQueueOverflow,
  ErrorCode_Timeout,
  ErrorCode_InvalidHeader,
  ErrorCode_HashMismatch
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///HS Connection log listener
///////////////////////////////////////////////////////////////////////////////////////////////////
class IHsConnectionLogListener
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///New log message
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void OnLogMessage (HsConnection& sender, const char* message) = 0;

  protected:
    virtual ~IHsConnectionLogListener () {}
};


///////////////////////////////////////////////////////////////////////////////////////////////////
///HS Connection events listener
///////////////////////////////////////////////////////////////////////////////////////////////////
class IHsConnectionEventListener
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///Connection error
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void OnError (HsConnection& sender, ErrorCode code, const char* error) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///New message
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void OnMessageReceived (HsConnection& sender, unsigned char sender_plugin_id, unsigned char receiver_plugin_id, const unsigned char* message, size_t size) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Connection connected
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void OnStateChanged (HsConnection& sender, HsConnectionState new_state) = 0;

  protected:
    virtual ~IHsConnectionEventListener () {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///HS Server Connection settings
///////////////////////////////////////////////////////////////////////////////////////////////////
struct HsConnectionSettings
{
  size_t        send_queue_size;         //max send queue size
  size_t        keep_alive_interval;     //keep alive messages interval in milliseconds (0 - disabled)
  bool          compression_enabled;     //is compression enabled
  size_t        compression_threshold;   //compress messages larger than threshold
  bool          encryption_enabled;      //is encryption enabled
  unsigned char encryption_key [32];     //encryption key
  size_t        encryption_key_bits;     //encryption key size
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///HS Server Connection
///////////////////////////////////////////////////////////////////////////////////////////////////
class HsConnection
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///Constructor / destructor
///////////////////////////////////////////////////////////////////////////////////////////////////
    HsConnection  (const HsConnectionSettings& settings);
    ~HsConnection ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///Connection
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Connect    (const char* host, unsigned short port);
    void Disconnect ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///Sending events
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SendMessage (unsigned short sender_plugin_id, unsigned short receiver_plugin_id, const unsigned char* message, size_t size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///Event listening
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                        SetEventListener (IHsConnectionEventListener* listener);
    void                        SetLogListener   (IHsConnectionLogListener* listener);
    IHsConnectionEventListener* EventListener    () const;
    IHsConnectionLogListener*   LogListener      () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Connection state
///////////////////////////////////////////////////////////////////////////////////////////////////
    HsConnectionState State () const;

  private:
    HsConnection (const HsConnection&);               //no impl
    HsConnection& operator = (const HsConnection&);   //no impl

  private:
    struct Impl;
    Impl* impl;
};

}

}

#endif
