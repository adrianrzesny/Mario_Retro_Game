#include "fireone.h"

#include "ComponentManager.h"
#include "ResourceFactory.h"
#include "Terrain.h"
#include "Goomba.h"
#include "Chimeny.h"

#include <cmath>
#include <ctime>

fireone::fireone(const Sprite &_sprite, float2 _position, float _orientation)
    :Entity(_sprite, _position, _orientation),
     movingDir(1)
{
    time = clock() + 3000;
    sprite.play(1,2);
}

fireone::~fireone()
{}

void fireone::update()
{

    velocity = float2((float)movingDir*0.04f, -.2f);
    position += velocity;

        a = a + 0.05f;
        b = 1.4f + cos(a);
        position = float2(a,b);

        if (a > 80)
        {
            c = c + 5;
            a = -10 + c;
            if (c > 40) c = 5;

        }

    sprite.update();
}


