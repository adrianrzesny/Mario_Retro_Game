#include <stdlib.h>

#include "Power.h"
#include "Mario.h"
#include "Luigi.h"
#include "ResourceFactory.h"
#include "Terrain.h"
#include "Coin.h"
#include "Goomba.h"
#include "Sprite.h"
#include "SpriteText.h"
#include "fire.h"
#include "fireone.h"

Mario::Mario(const Sprite &_sprite, float2 _position, float _orientation)
    :Entity(_sprite, _position, _orientation),
    forward(false), backward(false), left(false), right(false),
    movingDir(1), jumpPressed(false), jump(0)
{
    sprite.play(0,0);
}

Mario::~Mario()
{}

int Mario::money()
{
    return point;
}

void Mario::update()
{
    float2 position2;
    position2 = position;
    Goomba* goomba = collisionWith<Goomba>();
    if (goomba!=NULL)
    {
        float2 coll = collisionSeparate(goomba);
        if (goomba!=NULL)
        {
            float2 coll = collisionSeparate(goomba);
            if (fabs(coll.x)>fabs(coll.y))
                goomba->BitDw();
            else
               {
                   goomba->kill();
                    point++;
               }
        }
    }

    float2 targetSpeed(0, -.2f);
    if (left)
    {
        targetSpeed.x -= .2f;
        if (movingDir!=-1)
            sprite.play(5,7);
        movingDir=-1;
    }
    else if (right)
    {
        targetSpeed.x += .2f;
        if (movingDir!=1)
            sprite.play(1,3);
        movingDir=1;
    }
    else
    {
        if (movingDir==1)
            sprite.play(4,4);
        else if (movingDir==-1)
            sprite.play(0,0);
        sprite.pause();
        movingDir=0;
    }

    if (forward)
    {
        if (!jumpPressed)
        {
            jumpPressed = true;
            if ( fabs(Terrain::get().collisionWith('#', position + float2(0, -.1f), float2(.5f, .5f)).y - .1f) < 0.001f )
                jump = 14;
        }
        if (--jump>0)
            targetSpeed.y = .3f;
    }
    else
        jumpPressed = false;

    velocity = targetSpeed * .5f + velocity * .5f;
    if (velocity.len() < .02f) velocity.zero();
    position += velocity;

    float2 coll( Terrain::get().collisionWith('#', position, float2(.5f, .5f)));
    if (!coll.isZero())
    {
        position+=coll;
    }

    Coin *coin = collisionWith<Coin>();
    if (coin!=NULL)
    {
        coin->kill();
        point++;
    }

    fire *Fire = collisionWith<fire>();
    if (Fire!=NULL)
        {
            kill();
        }

    fireone *Fireone = collisionWith<fireone>();
    if (Fireone!=NULL)
        {
            kill();
        }

        Luigi* e = collisionWith<Luigi>();
        if (e!=NULL)
        {
                            if (forward)
                    {
                        if (!jumpPressed)
                        {
                            jumpPressed = true;
                            if ( fabs(Terrain::get().collisionWith('#', position + float2(0, -.1f), float2(.5f, .5f)).y - .1f) < 0.001f )
                                jump = 14;
                        }
                        if (--jump>0)
                            targetSpeed.y = .3f;
                    }
                    else
                    {

                        jumpPressed = false;
            position = position2;}
        }

    Power *power = collisionWith<Power>();
    if (power!=NULL)
        {
            power->UP();
        }

    sprite.update();
    Terrain::get().setViewPos(position);
}

void Mario::keyb(unsigned char k, bool down)
{
    if (!active) return;
    switch (k)
    {
    case 'w': forward = down; break;
    case 's': backward = down; break;
    case 'a': left = down; break;
    case 'd': right = down; break;
    case ' ': break;
    }
}

