#include <stdlib.h>

#include "Luigi.h"

#include "ResourceFactory.h"
#include "Terrain.h"
#include "Coin.h"
#include "Mario.h"
#include "Goomba.h"
#include "Power.h"
#include "fire.h"
#include "fireone.h"

#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>

Luigi::Luigi(const Sprite &_sprite, float2 _position, float _orientation)
    :Entity(_sprite, _position, _orientation),
    forward(false), backward(false), left(false), right(false),
    movingDir(1), jumpPressed(false), jump(0)
{
    sprite.play(0,0);
}

Luigi::~Luigi()
{}

int Luigi::money()
{
    return point;
}

void Luigi::update()
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

    Mario* e = collisionWith<Mario>();
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

    Coin *coin = collisionWith<Coin>();
    if (coin!=NULL)
    {
        coin->kill();
        point++;
    }


    Power *power = collisionWith<Power>();
    if (power!=NULL)
        {
            power->UP();
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

    sprite.update();
    Terrain::get().setViewPos(position);
}

void Luigi::keyb(int k, bool down)
{
    if (!active) return;
    switch (k)
    {
    case GLUT_KEY_UP: forward = down; break;
    case GLUT_KEY_DOWN: backward = down; break;
    case GLUT_KEY_LEFT: left = down; break;
    case GLUT_KEY_RIGHT: right = down; break;
    case ' ':

        break;
    }
}

