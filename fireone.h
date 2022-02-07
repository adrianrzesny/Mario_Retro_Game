#ifndef FIREONE_H
#define FIREONE_H

#include "Entity.h"

class fireone : public Entity
{
    public:
        fireone(const Sprite &, float2, float);
        virtual ~fireone();
        virtual void update();
        float a = -70.01;
        float b = 1.4f;
        int time = 0;
        int c = 2;
        bool create = false;
    protected:
        int movingDir;
    private:
};

#endif

