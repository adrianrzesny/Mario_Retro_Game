#ifndef Luigi_H
#define Luigi_H

#include "Entity.h"

class Luigi : public Entity
{
    public:
        Luigi(const Sprite &, float2, float);
        virtual ~Luigi();

        int money();
        int point = 0;
        void update();

        void keyb(int, bool);
    protected:
        bool forward, backward, left, right;
        int movingDir;
        bool jumpPressed;
        int jump;
    private:
};

#endif // Luigi_H

