#include <iostream>

using std::cout;
using std::endl;

#include "Entity.h"

Entity::Entity(const Sprite &_sprite, float2 _position, float _orientation)
    :sprite(_sprite), position(_position), orientation(_orientation),
    velocity(float2()), radius(.45f), hp(100)
{
    cout<<"Entity::Entity()"<<endl;
}

Entity::~Entity()
{
    cout<<"Entity::~Entity()"<<endl;
}

void Entity::draw()
{
    sprite.draw(position, orientation);
}

void Entity::update()
{
    sprite.update();
}

float2 Entity::collisionSeparate(Entity *e)
{
    float2 r;
    if ( (position - e->position).len() < radius + e->radius )
        r = (position-e->position).normalized()
            * (radius + e->radius - (position-e->position).len());
    return r;
}
