#include <stl/hash_map>
#include <stl/string>
#include <stl/vector>

#include <xtl/bind.h>
#include <xtl/common_exceptions.h>
#include <xtl/connection.h>
#include <xtl/function.h>
#include <xtl/trackable.h>
#include <xtl/token_parser.h>

#include <math/utility.h>

#include <bv/plane_list.h>

#include <common/singleton.h>

#include <sg/camera.h>
#include <sg/input.h>
#include <sg/scene.h>
#include <sg/screen.h>
#include <sg/viewport.h>

#include <input/scene_input.h>

namespace input
{

class InputScene;

typedef xtl::intrusive_ptr<InputScene> InputScenePtr;

typedef bound_volumes::plane_list<float> frustum;

typedef unsigned int touch_t;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum TouchState
{
  TouchState_Moving,
  TouchState_Pressed,
  TouchState_Released
};

const touch_t MOUSE_TOUCH_ID = touch_t (~0u); //������������� ���� ����

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct TouchEvent
{
  touch_t     touch;      //������������� ����
  int         button;     //������
  TouchState  state;      //��������� ����
  math::vec2f position;   //���������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputPort: public xtl::reference_counter, public scene_graph::IViewportListener, public xtl::noncopyable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputPort  (scene_graph::Viewport& in_viewport, bool& in_z_order_changed);
    ~InputPort ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    scene_graph::Viewport& AttachedViewport () { return viewport; }
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsActive () { return is_active; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    void OnViewportChangeArea       (const scene_graph::Rect& new_area, float min_depth_range, float max_depth_range);
    void OnViewportChangeCamera     (scene_graph::Camera* new_camera);
    void OnViewportChangeZOrder     (int);
    void OnViewportChangeActive     (bool new_state);
    void OnViewportChangeInputState (bool state);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetTouchSize (float size, InputTransformSpace);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void OnTouch (const TouchEvent& event, bool& touch_catched);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void ResetTouchState ();

  private:
    void OnSceneChanged  ();
    void OnCameraUpdated ();
    void Update ();

  private:
    scene_graph::Viewport&   viewport;               //������� ������
    bool&                    z_order_changed;        //������� ���������� �������� ����� �������
    InputScenePtr            input_scene;            //����� �����
    bool                     is_active;              //���������� �������
    bool                     need_update;            //����� ����������
    float                    touch_size;             //������ ����
    InputTransformSpace      touch_size_space;       //������� ��������� �������� ����
    math::vec3f              touch_scale;            //����������� ��������������� ����    
    xtl::auto_connection     on_camera_updated;      //���������� � �������� ���������� ������
    xtl::auto_connection     on_scene_changed;       //���������� � �������� ��������� �����
    math::mat4f              normalized_position_tm; //������� �������������� ��������� (� ������� ��������� ��������)
    math::mat4f              position_tm;            //������� �������������� ��������� (� ������� ������� ���������)
    math::mat4f              view_proj_tm;           //������� �������������� ��������� (proj * inv(view))
    math::mat4f              inv_view_proj_tm;       //������� ��������� �������������� ��������� (inv (proj * inv(view)))
    frustum                  touch_frustum;          //�������� ����
};

typedef xtl::intrusive_ptr<InputPort> InputPortPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputEventListener: public xtl::noncopyable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    class List: public xtl::noncopyable
    {
      friend class InputEventListener;
      public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
        List  ();
        ~List ();
        
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
        void BroadcastTouch (InputPort& input_port, const TouchEvent& event, const math::vec3f& touch_world_position);
        
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ����
///////////////////////////////////////////////////////////////////////////////////////////////////
        void DetachAll ();

      private:
        InputEventListener* first;
        InputEventListener* last;
    };
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputEventListener  ();
    ~InputEventListener ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void OnBroadcastTouch (InputPort& input_port, const TouchEvent& event, const math::vec3f& touch_world_position) {}

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� ��������� � ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Attach (List&);
    void Detach ();

  private:
    List*               list;
    InputEventListener* prev;
    InputEventListener* next;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputEntity: public xtl::reference_counter, private InputEventListener
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputEntity  (const scene_graph::InputZoneModel& zone, InputScene& scene);
    ~InputEntity ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ���� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const scene_graph::InputZoneModel& Zone () { return zone; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void OnTouch (InputPort& input_port, const TouchEvent& event, const math::vec3f& touch_world_position, size_t touch_zone_index, const math::vec2f& touch_local_position); 
    
  private:
    void OnBroadcastTouch    (InputPort& input_port, const TouchEvent& event, const math::vec3f& touch_world_position);
    void UpdateNotifications ();
  
  private:  
    const scene_graph::InputZoneModel& zone;
    InputScene&                        scene;
    xtl::auto_connection               on_notifications_changed_connection;
};

typedef xtl::intrusive_ptr<InputEntity> InputEntityPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputScene: public xtl::reference_counter, private InputEventListener::List
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputScene  (scene_graph::Scene& scene);
    ~InputScene ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    scene_graph::Scene& Scene () { return scene; }
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputEntityPtr GetEntity (const scene_graph::InputZoneModel&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void ResetTouchState ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void OnTouch (InputPort& input_port, const TouchEvent& event, const math::vec3f& touch_world_position, const math::vec3f& touch_world_direction, const frustum& touch_frustum, bool& touch_catched);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RegisterBroadcastListener (InputEventListener& listener);
    
  private:
    void OnInputZoneDestroyed (const scene_graph::InputZoneModel*);
    void OnInputZoneCreated   (scene_graph::Node&);
    
    struct EntityDesc
    {
      InputEntityPtr       entity;
      xtl::auto_connection on_unbind_connection;
    };
    
  private:
    typedef stl::hash_map<const scene_graph::InputZoneModel*, EntityDesc> EntityMap;

  private:    
    scene_graph::Scene&  scene;
    EntityMap            entities;
    xtl::auto_connection on_entity_created_connection;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputSceneCollection
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputSceneCollection  ();
    ~InputSceneCollection ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputScenePtr GetScene (scene_graph::Scene&);
    
  private:
    void OnSceneDestroyed (scene_graph::Scene*);    

  private:
    struct SceneDesc
    {
      InputScenePtr        scene;
      xtl::auto_connection on_scene_destroyed;
    };
  
    typedef stl::hash_map<scene_graph::Scene*, SceneDesc> InputSceneMap;    
    
  private:
    InputSceneMap scenes;
};

typedef common::Singleton<InputSceneCollection> InputSceneCollectionSingleton;

}