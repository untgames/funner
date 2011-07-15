#ifndef RENDER_MANAGER_CACHE_HEADER
#define RENDER_MANAGER_CACHE_HEADER

//TODO: �������� ������� ����� ��� ��������� �������� ����: ���������������� ������� ����������, ���������������� ��������

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum CacheState
{
  CacheState_Reset,   //��� �������
  CacheState_Valid,   //��� � ���������� ���������
  CacheState_Invalid, //��� � ������� ����������
  CacheState_Broken,  //��� � ������������ ���������, ��������� ������� ��� ���������� ����
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������, �������� ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class CacheHolder: public xtl::noncopyable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    CacheHolder  ();
    ~CacheHolder ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ ��������� ���������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AttachCacheSource     (CacheHolder& source);
    void DetachCacheSource     (CacheHolder& source);
    void DetachAllCacheSources ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    CacheState State () { return state; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsParentOf (CacheHolder& child);
    bool IsValid    () { return state == CacheState_Valid; }
    bool IsBroken   () { return state == CacheState_Broken; }

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ������������� ���������� ���� / ��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void InvalidateCache (bool invalidate_dependencies = true);
    void InvalidateCacheDependencies () { InvalidateCache (true); }
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void ResetCache ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����. ���������� �������� ����� ������ �������������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateCache ();

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� ������� ���������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////  
    virtual void UpdateCacheCore () = 0;
    virtual void ResetCacheCore  () = 0;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void InvalidateFlags ();

  private:
    typedef stl::list<CacheHolder*> HolderList;

  private:
    HolderList dependencies;
    HolderList sources;
    CacheState state;
    bool       need_update_this;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class CacheSource: public CacheHolder
{
  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� ������� ���������� ����.
///////////////////////////////////////////////////////////////////////////////////////////////////  
    void UpdateCacheCore ();
    void ResetCacheCore  ();
};

#endif
