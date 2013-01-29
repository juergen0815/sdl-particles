/*
 * texture.cpp
 *
 *  Created on: Jan 19, 2013
 *      Author: Jurgen
 */

#include "texture.h"

#include <GL/glew.h>

Texture::Texture()
    : m_TextID( -1 )
    , m_Width(0)
    , m_Height(0)
{
}

Texture::~Texture()
{
}

bool Texture::Allocate( int width, int height, int type )
{
    bool r(false);
    m_Width  = width;
    m_Height = height;
    glGenTextures( 1, (GLuint*)&m_TextID );
    GL_ASSERT( glGetError(), "Error generating texture!" );

    if ( glGetError() == GL_NO_ERROR ) {
        glBindTexture( GL_TEXTURE_2D, m_TextID );

        /* Linear Filtering */
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        // TODO: use flags to set wrap mode
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // TODO: use flags to switch mip maps on/off
        glTexParameterf(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

        // generate pixel buffer in vmem
        glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, NULL);
        r = true;
    }
    return r;
}

void Texture::Load( const char* pixels, int width, int height, int type )
{
    Enable();
    // load pixels into texture memory
    if ( width > m_Width || height > m_Height ) {
        // Size increased
        glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, NULL);
        m_Width  = width;
        m_Height = height;
    }
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, type, GL_UNSIGNED_BYTE, pixels);
}

void Texture::Bind()
{
    ASSERT( m_TextID > -1, "Invalid Texture ID" );

    /* Typical Texture Generation Using Data From The Bitmap */
    glBindTexture( GL_TEXTURE_2D, m_TextID );
}

void Texture::Enable()
{
    glEnable( GL_TEXTURE_2D );
    Bind();
}

void Texture::Disable()
{
    glDisable( GL_TEXTURE_2D );
}

