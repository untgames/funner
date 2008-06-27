#include <stl/hash_map>
#include <stl/list>
#include <stl/string>

#include <xtl/bind.h>
#include <xtl/common_exceptions.h>
#include <xtl/connection.h>
#include <xtl/function.h>
#include <xtl/intrusive_ptr.h>
#include <xtl/reference_counter.h>
#include <xtl/shared_ptr.h>
#include <xtl/signal.h>
#include <xtl/trackable.h>

#include <common/var_registry.h>
#include <common/singleton.h>
#include <common/strlib.h>

namespace common
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
class MountPoint : public xtl::trackable, public xtl::reference_counter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    MountPoint (const char* in_name, ICustomVarRegistry* in_registry) : name (in_name), registry (in_registry)
    {
      registry->SetEventHandler (xtl::bind (&MountPoint::Notify, this, _1, _2));
    }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name () const { return name.c_str (); }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ICustomVarRegistry* Registry () const { return registry.get (); }

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� ������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (const char* mount_point_name, const char* var_name, VarRegistryEvent event)> EventHandler;    

    xtl::connection RegisterEventHandler (const EventHandler& handler)
    {
      return signal.connect (handler);
    }

  private:
    void Notify (const char* var_name, VarRegistryEvent event)
    {
      signal (name.c_str (), var_name, event);
    }

  private:
    typedef xtl::com_ptr<ICustomVarRegistry>                               CustomVarRegistryPtr;
    typedef xtl::signal<void (const char*, const char*, VarRegistryEvent)> MountPointSignal;

  private:
    stl::string          name;
    CustomVarRegistryPtr registry;
    MountPointSignal     signal;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
class MountPointsMap
{
  public:
    typedef xtl::shared_ptr<MountPointsMap> Pointer;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ~MountPointsMap ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Mount      (const char* branch_name, ICustomVarRegistry* registry);
    void Unmount    (const char* branch_name);
    void UnmountAll ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    MountPoint* FindMountPoint (const char* full_var_name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� ������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    class IListener
    {
      public:
        virtual void OnMount   (MountPoint*) = 0;
        virtual void OnUnmount (MountPoint*) = 0;
    };

    void RegisterListener   (IListener*);
    void UnregisterListener (IListener*);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ����� ����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static Pointer GetGlobalMap ();

  private:
    typedef xtl::intrusive_ptr<MountPoint>                           MountPointPtr;
    typedef stl::hash_map<stl::hash_key<const char*>, MountPointPtr> MountMap;
    typedef stl::list<IListener*>                                    ListenersList;

  private:
    MountMap      mount_points_map;
    ListenersList listeners_list;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class VarRegistryImpl : public xtl::trackable, public xtl::reference_counter, private MountPointsMap::IListener
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    VarRegistryImpl  (const MountPointsMap::Pointer&, const char* branch_name);
    ~VarRegistryImpl ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������/��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetValue (const char* var_name);
          void  SetValue (const char* var_name, const char* value);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool HasVariable (const char* var_name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* BranchName ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ���� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef VarRegistry::EnumHandler EnumHandler;

    void EnumerateVars (const EnumHandler& handler);
    void EnumerateVars (const char* var_name_mask, const EnumHandler& handler);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� ����������/���������/�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef VarRegistry::EventHandler EventHandler;
    
    xtl::connection RegisterEventHandler (const char* var_name_mask, VarRegistryEvent event, const EventHandler& handler);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static VarRegistryImpl* GetNullBranch ();
    static VarRegistryImpl* CreateBranch  (const char* branch_name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � ���������/�������� ����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void OnMount   (MountPoint* new_mount_point);
    void OnUnmount (MountPoint* deleted_mount_point);

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����� ������������ �� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    MountPoint* FindMountPoint (const char* branch_name, stl::string& full_var_name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Notify (const char* mount_point_name, const char* var_name, VarRegistryEvent event);

  private:
    VarRegistryImpl (const VarRegistryImpl&); //no impl
    VarRegistryImpl& operator = (const VarRegistryImpl&); //no impl

  private:
    typedef xtl::signal<void (const char*)> VarRegistrySignal;

    struct AssignedMountPoint
    {
      AssignedMountPoint (MountPoint* in_mount_point, xtl::connection& in_event_connection)
        : mount_point (in_mount_point), event_connection (in_event_connection) {}

      MountPoint           *mount_point;
      xtl::auto_connection event_connection;
    };

    class RemoveIfPredicate;
    
    typedef xtl::shared_ptr<AssignedMountPoint> AssignedMountPointPtr;
    typedef stl::list<AssignedMountPointPtr>    MountPointsList;

  private:
    stl::string             branch_name;
    MountPointsMap::Pointer mount_points_map;
    MountPointsList         mount_points_list;
    VarRegistrySignal       signals [VarRegistryEvent_Num];
};

const char* get_prefix_end (const char* branch_name);

}
