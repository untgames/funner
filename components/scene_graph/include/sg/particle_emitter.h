#ifndef SCENE_GRAPH_PARTICLE_EMITTER_HEADER
#define SCENE_GRAPH_PARTICLE_EMITTER_HEADER

#include <sg/sprite.h>

namespace scene_graph
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///Particle emitter events
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ParticleEmitterEvent
{
  ParticleEmitterEvent_OnPlay,     //fires on emitter start (when ParticleEmitter::Play called)
  ParticleEmitterEvent_OnPause,    //fires on emitter pause (when ParticleEmitter::Pause called)

  ParticleEmitterEvent_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///Particles emitter
///////////////////////////////////////////////////////////////////////////////////////////////////
class ParticleEmitter: public VisualModel
{
  public:
    typedef xtl::com_ptr<ParticleEmitter>       Pointer;
    typedef xtl::com_ptr<const ParticleEmitter> ConstPointer;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Particles emitter creation. If particles_parent is null, particles will be generated in
///emitter coordinate space
///////////////////////////////////////////////////////////////////////////////////////////////////
    static Pointer Create (const char* particle_system_id, Node::Pointer particles_parent = 0, scene_graph::SpriteMode sprite_mode = SpriteMode_Default);

///////////////////////////////////////////////////////////////////////////////////////////////////
///Particle system identifier (as loaded in media::ParticleSystemLibrary)
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* ParticleSystemId () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Particles are emitted in coordinate space of this node
///////////////////////////////////////////////////////////////////////////////////////////////////
    Node::Pointer ParticlesParent () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Sprite mode
///////////////////////////////////////////////////////////////////////////////////////////////////
    scene_graph::SpriteMode SpriteMode () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Control simulation process
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Play      ();
    bool IsPlaying () const;
    void Pause     ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///Registration for ParticleEmitter events
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (ParticleEmitter& sender, ParticleEmitterEvent event)> EventHandler;

    xtl::connection RegisterEventHandler (ParticleEmitterEvent, const EventHandler& handler) const;

    using Entity::RegisterEventHandler;

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///Constructor / destructor
///////////////////////////////////////////////////////////////////////////////////////////////////
    ParticleEmitter  (const char* particle_system_id, Node::Pointer particles_parent, scene_graph::SpriteMode sprite_mode);
    ~ParticleEmitter ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///Method which is called when this node is visited
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AcceptCore (Visitor&);

  private:
    struct Impl;
    Impl* impl;
};

}

#endif
