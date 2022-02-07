#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
    public:
        Player(const Sprite &, float2, float);
        virtual ~Player();

        void update();

        void keyb(int, bool);
    protected:
        bool forward, backward, left, right;
        int movingDir;
        bool jumpPressed;
        int jump;
    private:
};

#endif // PLAYER_H
