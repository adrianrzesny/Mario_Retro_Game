#include "Coin.h"

#include "ComponentManager.h"
#include "ResourceFactory.h"
#include "Terrain.h"
#include "Goomba.h"
#include "Chimeny.h"


Coin::Coin(const Sprite &_sprite, float2 _position, float _orientation)
    :Entity(_sprite, _position, _orientation),
     movingDir(1)
{}

Coin::~Coin()
{}

void Coin::update()
{

    velocity = float2((float)movingDir*0.04f, -.2f);
    position += velocity;
    float2 coll( Terrain::get().collisionWith('#', position, float2(.5f, .5f)));
    if (!coll.isZero())
    {
        position+=coll;
    }
    if (coll.x!=0) movingDir =- movingDir;

    Coin* e = collisionWith<Coin>(this);
        if (e!=NULL)
        {
            float2 coll = collisionSeparate(e);
                if (fabs(coll.x)>fabs(coll.y))
                {
                    movingDir =- movingDir;
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
         }

      Goomba* n = collisionWith<Goomba>();
        if (n!=NULL)
        {
            movingDir =- movingDir;
         }

    sprite.update();
}
