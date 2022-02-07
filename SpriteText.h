#ifndef SPRITETEXT_H
#define SPRITETEXT_H

#include "Sprite.h"

#include <string>

using std::string;

class SpriteText
{
    public:
        SpriteText(const Sprite&);
        virtual ~SpriteText();

        virtual void draw(float2, float, float);

        virtual void setText(const char *);
        virtual void setText(const char *, int);
        virtual void setText(const char *, int,const char *, int,const char *, int);

        virtual void setColor(float, float, float);
    protected:
        string text;
        Sprite sprite;
        float color[3];
    private:
};

#endif // SPRITETEXT_H
