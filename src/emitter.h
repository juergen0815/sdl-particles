
//**************************************************************************
// File: emitter.h
// Date: Jan 17, 2013
// Author: Jurgen
//**************************************************************************

#ifndef __emitter_h__
#define __emitter_h__

#include "err.h"
#include "particle.h"
#include "texture.h"

#include <list>

typedef std::list< ParticlePtr > ParticleList;

class Renderer;

class Emitter : public Entity
{
    ParticleList m_Particles;   // list to all particles
    TexturePtr   m_Texture;

    Renderer    *m_Renderer;    // keep a week link to the renderer
public:
    Emitter( Renderer* renderer );

    ~Emitter();

    bool HandleEvent( const SDL_Event& event );

private:
    bool OnUpdate( float ticks );

    virtual bool Initialize( Renderer* renderer );

    virtual void Render( float ticks );

    virtual void PostRender( );
};

#endif // __emitter_h__
