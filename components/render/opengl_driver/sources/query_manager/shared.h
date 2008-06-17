#ifndef RENDER_GL_DRIVER_QUERY_MANAGER_SHARED_HEADER
#define RENDER_GL_DRIVER_QUERY_MANAGER_SHARED_HEADER

#include <xtl/common_exceptions.h>
#include <xtl/trackable_ptr.h>

#include <shared/context_object.h>
#include <shared/query_manager.h>

namespace render
{

namespace low_level
{

namespace opengl
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ��������� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum QueryManagerCache
{
  QueryManagerCache_IsInRanges    //��������� �� � ������ begin-end
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� � ����������� �������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IAsyncPredicate : virtual public IPredicate
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual bool IsResultAvailable () = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������, ����������� ��� ���������� ���������� ��������� occlusion query
///////////////////////////////////////////////////////////////////////////////////////////////////
class NullPredicate : virtual public IAsyncPredicate, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    NullPredicate  (const ContextManager& manager) : ContextObject (manager) {}
    ~NullPredicate () {}

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Begin () {}
    void End   () {}

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ���������
///  (�������� ����� �������� � ��������� ���������� ���� �� ���������� ���������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool GetResult () {return true;}

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsResultAvailable () {return true;}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� � ����������� �������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class AsyncPredicate : virtual public IAsyncPredicate, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    AsyncPredicate  (const ContextManager&);
    ~AsyncPredicate ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Begin ();
    void End   ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ���������
///  (�������� ����� �������� � ��������� ���������� ���� �� ���������� ���������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool GetResult ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsResultAvailable ();

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ��������������� ���������, ���� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void MakeCurrentContextParent ();

  private:
    GLuint query;          //OpenGL id �������
    size_t parent_context; //�������������� ��������
};

}

}

}

#endif
