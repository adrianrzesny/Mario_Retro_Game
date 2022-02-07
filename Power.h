#ifndef POWER_H
#define POWER_H

#include "Entity.h"
#include<ctime>

class Power : public Entity
{
    public:
        Power(const Sprite &, float2, float);
        virtual ~Power();
        virtual UP();
        virtual Refresh();
        int time = 0;
    protected:
    private:
};

#endif // POWER_H

