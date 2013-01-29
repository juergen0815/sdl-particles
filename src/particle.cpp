/*
 * particle.cpp
 *
 *  Created on: 2013-01-17
 *      Author: jurgens
 */

#include "particle.h"

#include <GL/glew.h>

#include <cstdlib>

Particle::Particle( const Vector& color /* = Vector(1.0f, 0.3f,0.5f) */ )
    : m_LifeTime( 1.0f )
    , m_Color( color )
    , m_Gravity ( 0.0f, -0.8f, 0.0f )
    , m_Speed( 0.0f, 0.0f, 0.0f )
{
    Reset();
}

Particle::~Particle()
{
    m_Texture = TexturePtr();
}

void Particle::SetTexture( TexturePtr texture )
{
    m_Texture = texture;
}

bool Particle::Initialize( Renderer* renderer )
{
    // We'd load our texture here
    return true;
}

void Particle::Render( float ticks )
{
    bool remove = OnUpdate(ticks);
    if (!remove) {
        float x = m_Position[Vector::X];
        float y = m_Position[Vector::Y];
        float z = m_Position[Vector::Z];
        // make this vertex arrays...
        glColor4f( m_Color[ Vector::R], m_Color[ Vector::G], m_Color[ Vector::B], m_Color[ Vector::A] );
        glBegin( GL_TRIANGLE_STRIP );
            glTexCoord2s(1,1); glVertex3f( x+0.5f, y+0.5f, z);
            glTexCoord2s(0,1); glVertex3f( x-0.5f, y+0.5f, z);
            glTexCoord2s(1,0); glVertex3f( x+0.5f, y-0.5f, z);
            glTexCoord2s(0,0); glVertex3f( x-0.5f, y-0.5f, z);
        glEnd();
    }
}

void Particle::PostRender()
{
}

void Particle::Reset()
{
    SetFlag( Entity::F_ENABLE );
    m_Slowdown = 10.0f;
    m_LifeTime = 1.0f;
    m_FadeTime = float( rand( ) %100 ) / 1000.0f + 0.003f;
    m_Direction = { m_Speed[Vector::X] + float((std::rand()%50)-26.0f)*10.0f ,
                    m_Speed[Vector::Y] + float((std::rand()%50)-25.0f)*10.0f ,
                    m_Speed[Vector::Z] + float((std::rand()%50)-25.0f)*10.0f };
    m_Position = { 0,0,0,0 };
}

bool Particle::OnUpdate( float ticks )
{
    bool remove(false);

    /* Move On The X Axis By X Speed */
    m_Position  += (m_Direction * ( ticks / (m_Slowdown * 1000.0f)) );
    m_Direction += m_Gravity;
    m_LifeTime  -= m_FadeTime;
    if ( m_LifeTime < 0.0f )
    {
        Reset();
    }
    return remove;
}
