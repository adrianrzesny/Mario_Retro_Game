#ifndef PORTAL_H
#define PORTAL_H

#include "Entity.h"

class Portal : public Entity
{
    public:
        Portal(float2, float, float2);
        Portal(const Sprite &, float2, float);
        virtual ~Portal();

        void update();
        void draw() {}
    protected:
        float2 moveTo;
    private:
};

#endif // PORTAL_H
