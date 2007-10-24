#include <stl/hash_map>
#include <xtl/signal.h>
#include <xtl/bind.h>
#include <common/exception.h>
#include <syslib/timer.h>
#include <sg/scene.h>
#include <sg/node.h>
#include <sg/entity.h>
#include <sg/listener.h>
#include <sg/sound_emitter.h>
#include <sound/sgplayer.h>
#include <math/mathlib.h>

using namespace sound;
using namespace syslib;
using namespace xtl;
using namespace common;
using namespace scene_graph;
using namespace math;

#ifdef _MSC_VER
  #pragma warning (disable : 4355) //'this' : used in base member initializer list
#endif

const float DEFAULT_LISTENER_PROPERTIES_UPDATE_PERIOD = 0.03f;
const float DEFAULT_EMITTER_PROPERTIES_UPDATE_PERIOD = 0.03f;

/*
    �������� ���������� SGPlayer
*/

struct SGPlayerEmitter
{
  sound::Emitter        emitter;     //�������

  SGPlayerEmitter (SoundEmitter* sound_emitter, const char* source_name);
  SGPlayerEmitter (const SGPlayerEmitter& source);
};

SGPlayerEmitter::SGPlayerEmitter (SoundEmitter* sound_emitter, const char* source_name) 
  : emitter (source_name) 
  {}

SGPlayerEmitter::SGPlayerEmitter (const SGPlayerEmitter& source)
  : emitter (source.emitter.Source ())
  {}

typedef stl::hash_map<scene_graph::SoundEmitter*, SGPlayerEmitter> EmitterSet;

struct SGPlayer::Impl
{
  scene_graph::Listener& listener;           //���������
  sound::SoundManager&   sound_manager;      //��������
  EmitterSet             emitters;           //��������
  Timer                  listener_timer;     //������ ���������� ���������
  Timer                  emitter_timer;      //������ ���������� ���������

  Impl (scene_graph::Listener& in_listener, sound::SoundManager& in_sound_manager);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� ���������/���������
///////////////////////////////////////////////////////////////////////////////////////////////////
  void ListenerUpdate ();
  void EmitterUpdate  ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� Node ����� � ������, ���� �������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
  void CheckNode (scene_graph::Node& node);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������/�������� ����� � �����
///////////////////////////////////////////////////////////////////////////////////////////////////
  void ProcessAttachNode (Node& sender, Node& node, NodeSubTreeEvent event);
  void ProcessDetachNode (Node& sender, Node& node, NodeSubTreeEvent event);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
  void PlayEmitter (SoundEmitter& emitter, SoundEmitterEvent event);
  void StopEmitter (SoundEmitter& emitter, SoundEmitterEvent event);
};

SGPlayer::Impl::Impl (scene_graph::Listener& in_listener, sound::SoundManager& in_sound_manager) 
  : listener (in_listener), 
    sound_manager (in_sound_manager), 
    listener_timer (xtl::bind (&SGPlayer::Impl::ListenerUpdate, this), (size_t)(DEFAULT_LISTENER_PROPERTIES_UPDATE_PERIOD * 1000)),
    emitter_timer (xtl::bind (&SGPlayer::Impl::EmitterUpdate, this), (size_t)(DEFAULT_EMITTER_PROPERTIES_UPDATE_PERIOD * 1000))
{
  scene_graph::Scene* scene = listener.Scene ();

  if (!scene)
    Raise <Exception> ("sound::SGPlayer::Impl::Impl", "Listener is not binded to any scene.");

  scene->Traverse (xtl::bind (&SGPlayer::Impl::CheckNode, this, _1));

  scene->Root ().Event (NodeSubTreeEvent_AfterBind).connect  (bind (&SGPlayer::Impl::ProcessAttachNode, this, _1, _2, _3));
  scene->Root ().Event (NodeSubTreeEvent_BeforeUnbind).connect (bind (&SGPlayer::Impl::ProcessDetachNode, this, _1, _2, _3));
}

/*
   ���������� ������� ���������/���������
*/

void SGPlayer::Impl::ListenerUpdate ()
{
  sound::Listener snd_listener;
    
  snd_listener.position  = listener.WorldPosition ();                              //!!!!!!!!�������� ��������
  snd_listener.direction = listener.WorldOrientation () * vec3f(0.f,0.f,1.f);
  snd_listener.up        = listener.WorldOrientation () * vec3f(0.f,1.f,0.f);

  sound_manager.SetListener (snd_listener);
}

void SGPlayer::Impl::EmitterUpdate ()
{
  for (EmitterSet::iterator i = emitters.begin (); i != emitters.end (); ++i)                   //!!!!!!!!�������� ��������
  {
    i->second.emitter.SetPosition (i->first->WorldPosition ());
    i->second.emitter.SetDirection (i->first->WorldOrientation () * vec3f(0.f,0.f,1.f));
  }
}

/*
   ���������� Entity ����� � ������, ���� �������� ���������
*/

void SGPlayer::Impl::CheckNode (scene_graph::Node& node)
{
  scene_graph::SoundEmitter* emitter = dynamic_cast<scene_graph::SoundEmitter*> (&node);

  if (emitter)
  {
    SGPlayerEmitter sgplayer_emitter (emitter, emitter->SoundDeclarationName ());

    emitters.insert_pair (emitter, sgplayer_emitter);
    emitter->Event (SoundEmitterEvent_Play).connect (bind (&SGPlayer::Impl::PlayEmitter, this, _1, _2));
    emitter->Event (SoundEmitterEvent_Stop).connect (bind (&SGPlayer::Impl::StopEmitter, this, _1, _2));
  }
}

/*
   ��������� ����������/�������� ����� � �����
*/

void SGPlayer::Impl::ProcessAttachNode (Node& sender, Node& node, NodeSubTreeEvent event)
{
  CheckNode (node);
}

void SGPlayer::Impl::ProcessDetachNode (Node& sender, Node& node, NodeSubTreeEvent event)
{
  EmitterSet::iterator emitter_iter = emitters.find ((scene_graph::SoundEmitter*) (&node));

  if (emitter_iter == emitters.end ())
    return;

  emitters.erase (emitter_iter);
}

/*
   ������������ ���������
*/

void SGPlayer::Impl::PlayEmitter (SoundEmitter& emitter, SoundEmitterEvent event)
{
  EmitterSet::iterator emitter_iter = emitters.find ((scene_graph::SoundEmitter*) (&emitter));

  if (emitter_iter == emitters.end ())
    return;

  sound_manager.PlaySound (emitter_iter->second.emitter);
}

void SGPlayer::Impl::StopEmitter (SoundEmitter& emitter, SoundEmitterEvent event)
{
  EmitterSet::iterator emitter_iter = emitters.find ((scene_graph::SoundEmitter*) (&emitter));

  if (emitter_iter == emitters.end ())
    return;

  sound_manager.StopSound (emitter_iter->second.emitter);
}

/*
   ����������� / ����������
*/

SGPlayer::SGPlayer (scene_graph::Listener& listener, sound::SoundManager& sound_manager)
  : impl (new Impl (listener, sound_manager))
  {}

SGPlayer::~SGPlayer ()
{
}


