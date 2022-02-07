#include "Goomba.h"

#include "Coin.h"
#include "ResourceFactory.h"
#include "Terrain.h"
#include "Ret.h"
#include "Chimeny.h"
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include "ComponentManager.h"
#include "Mario.h"
#include "Luigi.h"

Goomba::Goomba(const Sprite &_sprite, float2 _position, float _orientation)
    :Entity(_sprite, _position, _orientation),
    movingDir(-1)
{
    sprite.play(3,4);
}

Goomba::~Goomba()
{}

void Goomba::Speed()
{
    speed = 0.34f;
    sprite.play(13,14);
}

void Goomba::Stop()
{
    speed = 0.f;
    if (level == 1)
    sprite.play(5,5);
    if (level == 2)
    sprite.play(10,10);
    if (level == 3)
    sprite.play(15,15);
    if (level == 4)
    sprite.play(15,15);

}

void Goomba::Stan()
{
    Stat = true;
    time = clock() + 1500;
}

void Goomba::Graf()
{
    if (level == 1)
        {
            if (movingDir == 1)
            {
                sprite.play(1,2);
            }
            if (movingDir == -1)
            {
                sprite.play(3,4);
            }
        }
    else if (level == 2)
    {
        if (movingDir == 1)
        {
            sprite.play(6,7);
        }
        if (movingDir == -1)
        {
            sprite.play(8,9);
        }

    }
    else if (level == 3)
        {
            if (movingDir == 1)
            {
                sprite.play(11,12);
            }
            if (movingDir == -1)
            {
                sprite.play(13,14);
            }
        }
    else if (level == 4)
           {
               if (movingDir == 1)
            {
                sprite.play(11,12);
            }
            if (movingDir == -1)
            {
                sprite.play(13,14);
            }
           }
}

void Goomba::Start()
{
    if (level == 1)
        {
            level =2;
            speed = 0.09f;
        }
    else if (level == 2)
    {
            level = 3;
            speed = 0.11f;
    }
    else if (level == 3)
        {
            level = 4;
            Speed();
        }

    else if (level == 4)
    {
        Speed();
    }

    Stat = false;
    Graf();
}


void Goomba::BitDw()
{

    if (Stat)
    {
        kill();
    }
    else
    {
        Mario* mario = collisionWith<Mario>();
        if (mario!=NULL)
            mario->kill();
        Luigi* luigi = collisionWith<Luigi>();
        if (luigi!=NULL)
            luigi->kill();
    }
}

void Goomba::update()
{

    if (Stat)
    {
        Stop();
        if (time < clock())
            Start();
    }

    velocity = float2((float)movingDir*speed, -.2f);
    position += velocity;
    float2 coll( Terrain::get().collisionWith('#', position, float2(.5f, .5f)));
    if (!coll.isZero())
    {
        position+=coll;
    }
    if (coll.x!=0) movingDir =- movingDir;


    Goomba* e = collisionWith<Goomba>(this);
        if (e!=NULL)
        {
            float2 coll = collisionSeparate(e);
                if (fabs(coll.x)>fabs(coll.y))
                {
                    movingDir =- movingDir;
                    Graf();
                }
                else if (e!=NULL)
                        {
                            e->setPosition(float2(3,11));
                        }

        }


     Chimeny* r = collisionWith<Chimeny>();
        if (r!=NULL)
        {
            movingDir =- movingDir;
            Graf();
         }

      Coin* n = collisionWith<Coin>();
        if (n!=NULL)
        {
            movingDir =- movingDir;
            Graf();
         }


    sprite.update();
}
