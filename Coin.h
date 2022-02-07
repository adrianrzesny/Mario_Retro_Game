#ifndef COIN_H
#define COIN_H

#include "Entity.h"

class Coin : public Entity
{
    public:
        Coin(const Sprite &, float2, float);
        virtual ~Coin();
        virtual void update();
        bool create = false;
    protected:
        int movingDir;
    private:
};

#endif // COIN_H
