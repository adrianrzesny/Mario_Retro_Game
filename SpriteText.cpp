#include <gl/gl.h>

#include <sstream>

using std::ostringstream;

#include "SpriteText.h"

SpriteText::SpriteText(const Sprite& _sprite)
    : sprite(_sprite), color{1.f, 1.f, 1.f}
{}

SpriteText::~SpriteText()
{}

void SpriteText::draw(float2 position, float orientation, float scale)
{
    if (text.empty()) return;
    glPushMatrix();
    glColor3fv(color);
    glLoadIdentity();
    glTranslatef(position.x, position.y, -1.f);
    glRotatef(orientation, 0,0,1);
    glScalef(scale, scale, scale);
    for (unsigned int i=0; i<text.length(); ++i)
    {
        sprite.play( text[i], text[i] );
        sprite.draw(float2(i,0), 0.f, 1.f);
    }
    glColor3f(1.f, 1.f, 1.f);
    glPopMatrix();
}

void SpriteText::setColor(float r, float g, float b)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void SpriteText::setText(const char *s)
{
    text = s;
}

void SpriteText::setText(const char *s, int i)
{
    ostringstream o;
    o<<s<<i;
    text = o.str();
}

void SpriteText::setText(const char *s, int i,const char *q, int w,const char *r, int t)
{
    ostringstream o;
    o<<s<<i<<q<<w<<r<<t;
    text = o.str();
}
