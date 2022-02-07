#ifndef FIRE_H
#define FIRE_H

#include "Entity.h"

class fire : public Entity
{
    public:
        fire(const Sprite &, float2, float);
        virtual ~fire();
        virtual void update();
        float a = -50.01;
        float b = 7.4f;
        int time = 0;
        int c = 2;
        bool create = false;
    protected:
        int movingDir;
    private:
};

#endif
