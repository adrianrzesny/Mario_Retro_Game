#ifndef Mario_H
#define Mario_H

#include "Entity.h"

class Mario : public Entity
{
    public:
        Mario(const Sprite &, float2, float);
        virtual ~Mario();
        void update();
        int money();
        int point = 0;
        void keyb(unsigned char, bool);
    protected:
        bool forward, backward, left, right;
        int movingDir;
        bool jumpPressed;
        int jump;
    private:
};

#endif // PLAYER_H

