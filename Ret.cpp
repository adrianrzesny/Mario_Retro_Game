#include "Ret.h"
#include "Goomba.h"
#include "Coin.h"
#include<cstdlib>
#include<ctime>


Ret::Ret(float2 _position, float _orientation, float2 _moveTo)
             :Entity(Sprite(NULL), _position, _orientation), moveTo(_moveTo)
{}

Ret::~Ret()
{}

void Ret::update()
{
    Entity *e;
    e = collisionWith<Goomba>();
    int i = ComponentManager::get().count<Goomba>();
    while (i--)
    {
        if (e!=NULL)
            {
            srand(static_cast<unsigned int>(time(NULL)));
            int los =  rand() % 2 + 1;
            float a = 2;
            float b = 24;
           if (los == 1)
                e->setPosition(float2(2,11));
            else e->setPosition(float2(b,11));
            }
    }

    e = collisionWith<Coin>();
    i = ComponentManager::get().count<Coin>();
    while (i--)
    {
        if (e!=NULL)
            {
            srand(static_cast<unsigned int>(time(NULL)));
            int los =  rand() % 2 + 1;
            float a = 2;
            float b = 24;
           if (los == 1)
                e->setPosition(float2(2,11));
            else e->setPosition(float2(b,11));
            }
    }

}


