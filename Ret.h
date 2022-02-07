#ifndef RET_H
#define RET_H

#include "Entity.h"

class Ret : public Entity
{
    public:
        Ret(float2, float, float2);
        Ret(const Sprite &, float2, float);
        virtual ~Ret();

        void update();
        void draw() {}
    protected:
        float2 moveTo;
    private:
};

#endif // RET_H
