#include "PortalT.h"

#include "Luigi.h"
#include "Mario.h"
#include "Goomba.h"
#include "Coin.h"

PortalT::PortalT(float2 _position, float _orientation, float2 _moveTo)
             :Entity(Sprite(NULL), _position, _orientation), moveTo(_moveTo)
{}

PortalT::~PortalT()
{}

void PortalT::update()
{
    Entity *e;
    e = collisionWith<Luigi>();
        if (e!=NULL)
            {
                e->setPosition(moveTo-0.1);
            }
    e = collisionWith<Mario>();
        if (e!=NULL)
            e->setPosition(moveTo-0.1);
    int i = ComponentManager::get().count<Goomba>();
    while (i--)
    {
        e = collisionWith<Goomba>();
            if (e!=NULL)
                e->setPosition(moveTo-0.1);
    }
    i = ComponentManager::get().count<Coin>();
    while (i--)
    {
        e = collisionWith<Coin>();
            if (e!=NULL)
                e->setPosition(moveTo-0.1);
    }
}


