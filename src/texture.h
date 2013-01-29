/*
 * texture.h
 *
 *  Created on: Jan 19, 2013
 *      Author: Jurgen
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "err.h"

#include <GL/glew.h>

#include <boost/shared_ptr.hpp>

class Texture
{
    int m_TextID;
    int m_Width, m_Height;
public:
    Texture();

    ~Texture();

    bool Allocate( int width, int height, int type = GL_RGBA );

    void Load( const char* pixels, int width, int height, int type = GL_RGBA );

    void Bind();

    void Enable();

    void Disable();
};

typedef boost::shared_ptr<Texture> TexturePtr;


#endif /* TEXTURE_H_ */
