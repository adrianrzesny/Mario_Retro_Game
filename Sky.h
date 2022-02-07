#ifndef Sky_H
#define Sky_H

#include "Entity.h"

class Sky : public Entity
{
    public:
        Sky(const Sprite &, float2, float);
        virtual ~Sky();
    protected:
    private:
};

#endif // Sky_H

