//************************************************************************
// File: emitter.cpp
// Date: Jan 17, 2013
// Author: Jurgen
//************************************************************************

#include "emitter.h"
#include "renderer.h"
#include "texture.h"
#include "brush.h"

#include <GL/glew.h>

#include <SDL/SDL.h>

#include <boost/bind.hpp>

extern struct Brush sParticleTexture;

const int NUM_PARTICLES = 10000;
const static int NUM_COLORS = 12;
static Vector sColors[NUM_COLORS] =               // Rainbow Of Colors
{
    {1.0f,0.5f,0.5f},{1.0f,0.75f,0.5f},{1.0f,1.0f,0.5f},{0.75f,1.0f,0.5f},
    {0.5f,1.0f,0.5f},{0.5f,1.0f,0.75f},{0.5f,1.0f,1.0f},{0.5f,0.75f,1.0f},
    {0.5f,0.5f,1.0f},{0.75f,0.5f,1.0f},{1.0f,0.5f,1.0f},{1.0f,0.5f,0.75f}
};

Emitter::Emitter(Renderer* renderer)
    : m_Texture( new Texture() )
    , m_Renderer( renderer )
{
    // TODO: Register frame call back to renderer
    ASSERT( renderer, "Error! Renderer is invalid!" );

    renderer->RegisterUpdateFunction( boost::bind( &Emitter::OnUpdate, this, _1 ) );

    for ( int i = 0; i < NUM_PARTICLES; ++i ) {
        ParticlePtr particle( new Particle( sColors[i*NUM_COLORS/NUM_PARTICLES] ) );
        particle->SetFlag( Entity::F_ENABLE );
        // not sure if I want to store them here
        m_Particles.push_back( particle );
    }

}

Emitter::~Emitter()
{
    m_Particles.clear();
}

bool Emitter::HandleEvent( const SDL_Event& event )
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_SPACE:
            break;
        default:
            break;
        }
        break;
    }

    return false;
}

bool Emitter::OnUpdate( float ticks )
{
    ASSERT( m_Renderer, "Invalid Renderer!" );

    return false; // true removes updater
}

bool Emitter::Initialize( Renderer* renderer )
{
    bool r(true);

    m_Texture->Allocate( sParticleTexture.m_Width, sParticleTexture.m_Height, GL_RGBA );
    m_Texture->Load( sParticleTexture.m_Pixels, sParticleTexture.m_Width, sParticleTexture.m_Height, GL_RGBA );
    for ( ParticlePtr& particle : m_Particles ) {
//        particle->SetTexture( m_Texture );
        particle->Initialize( renderer );
    }

    return r;
}

void Emitter::Render( float ticks )
{
    glPushMatrix();

    int gl_blend_src, gl_blend_dst;
    glGetIntegerv(GL_BLEND_SRC, &gl_blend_src);
    glGetIntegerv(GL_BLEND_DST, &gl_blend_dst);

    int blend_enabled;
    glGetIntegerv(GL_BLEND, &blend_enabled);
    if (!blend_enabled) glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_ALPHA_TEST );

    ASSERT( m_Texture, "Missing texture! Bailing out!" );
    m_Texture->Enable();
    for ( ParticlePtr& particle : m_Particles ) {
        particle->Render( ticks );
    }
    if ( !blend_enabled ) {
        glDisable(GL_ALPHA_TEST);
    }
    glBlendFunc( gl_blend_src, gl_blend_dst);
    m_Texture->Disable();

    glPopMatrix();
}

void Emitter::PostRender( )
{
}
