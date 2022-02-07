#include "Power.h"
#include "Goomba.h"
#include "Goomba.h"
#include<ctime>

Power::Power(const Sprite &_sprite, float2 _position, float _orientation)
    :Entity(_sprite, _position, _orientation)
{
    sprite.play(1,1);
}

Power::Refresh()
{
    health = 3;
    sprite.play(1,1);
}

Power::UP()
{
    if (health == 0)
        kill();
    else
    {
        if (time < clock())
        {
        health--;
        time = clock() + 1000;
            if (health == 2)
            sprite.play(2,2);
            if (health == 1)
                sprite.play(3,3);

                ComponentManager::get().find<Goomba>();
                Goomba* goomba = ComponentManager::get().next<Goomba>();
                goomba->Stan();
        }
    }

}


Power::~Power()
{}

