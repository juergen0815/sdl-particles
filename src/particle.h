/*
 * particle.h
 *
 *  Created on: 2013-01-17
 *      Author: jurgens
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

// http://nehe.gamedev.net/tutorial/particle_engine_using_triangle_strips/21001/

#include "err.h"
#include "vector.h"
#include "entity.h"
#include "texture.h"

#include <boost/shared_ptr.hpp>

class Particle : public Entity
{
    float  m_LifeTime;
    float  m_FadeTime;

    Vector m_Color;
    Vector m_Position;
    Vector m_Direction;
    Vector m_Gravity;

    Vector m_Speed;
    float  m_Slowdown;

    TexturePtr m_Texture;
public:
    Particle( const Vector& color = Vector( 1.0f, 0.3f,0.5f ) );

    ~Particle();

    void SetTexture( TexturePtr texture );
protected:
    virtual bool Initialize( Renderer* renderer );

    virtual void Render( float ticks );

    virtual void PostRender();
private:
    void Reset();

    bool OnUpdate( float ticks );

    friend class Emitter;
};

typedef boost::shared_ptr<Particle> ParticlePtr;

#endif /* PARTICLE_H_ */
