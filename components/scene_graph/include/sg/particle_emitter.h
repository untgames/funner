#ifndef SCENE_GRAPH_PARTICLE_EMITTER_HEADER
#define SCENE_GRAPH_PARTICLE_EMITTER_HEADER

#include <sg/visual_model.h>

namespace scene_graph
{

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
    static Pointer Create (const char* particle_system_id, Node::Pointer particles_parent = 0);

///////////////////////////////////////////////////////////////////////////////////////////////////
///Particle system identifier (as loaded in media::ParticleSystemLibrary)
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* ParticleSystemId () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Particles are emitted in coordinate space of this node
///////////////////////////////////////////////////////////////////////////////////////////////////
    Node::Pointer ParticlesParent () const;

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///Constructor / destructor
///////////////////////////////////////////////////////////////////////////////////////////////////
    ParticleEmitter  (const char* particle_system_id, Node::Pointer particles_parent);
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
