#ifndef SYSLIB_WEV_VIEW_HEADER
#define SYSLIB_WEV_VIEW_HEADER

#include <syslib/window.h>

namespace syslib
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������� ������ ���-������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum WebViewEvent
{
  WebViewEvent_OnLoadStart,  //���������� � ������ �������� ������
  WebViewEvent_OnLoadFinish, //���������� � ����� �������� ������
  WebViewEvent_OnLoadFail,   //���������� � ������ ������ ��� �������� ������
  WebViewEvent_OnClose,      //���������� ����� �������� ����
  WebViewEvent_OnDestroy,    //���������� ��� ����������� WebView
  
  WebViewEvent_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ ���-������
///////////////////////////////////////////////////////////////////////////////////////////////////
class WebView: public xtl::dynamic_cast_root //������!!!
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    WebView ();
    ~WebView ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const syslib::Window& Window () const;
          syslib::Window& Window ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LoadRequest (const char* uri);
    void LoadData    (const char* data, size_t data_size, const char* mime_type, const char* encoding, const char* base_url);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ �������� / ��������� �������� / �������� ������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    void Reload      ();
    void StopLoading ();
    bool IsLoading   () const;    

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� ������� / ������ ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Request () const;
    const char* Status  () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool CanGoBack    () const;
    bool CanGoForward () const;
    void GoBack       ();
    void GoForward    ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<bool (WebView& view, const char* request)> Filter;

    xtl::connection RegisterFilter (const Filter& filter) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (WebView& view, WebViewEvent event)> EventHandler;

    xtl::connection RegisterEventHandler (WebViewEvent event, const EventHandler& handler) const;

  private:
    WebView (const WebView&); //no implementation
    WebView& operator = (const WebView&); //no implementation

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

#endif