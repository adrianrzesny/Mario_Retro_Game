#ifndef PORTALT_H
#define PORTALT_H

#include "Entity.h"

class PortalT : public Entity
{
    public:
        PortalT(float2, float, float2);
        PortalT(const Sprite &, float2, float);
        virtual ~PortalT();

        void update();
        void draw() {}
    protected:
        float2 moveTo;
    private:
};

#endif // PORTAL_H

