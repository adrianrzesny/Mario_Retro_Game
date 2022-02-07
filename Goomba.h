#ifndef GOOMBA_H
#define GOOMBA_H

#include "Entity.h"
#include<ctime>

class Goomba : public Entity
{
    public:
        Goomba(const Sprite &, float2, float);
        virtual ~Goomba();
        virtual void Speed();
        virtual void Stop();
        virtual void Stan();
        virtual void Start();
        virtual void BitDw();
        virtual void Graf();
        float speed = 0.04f;
        int CompleteEnemy = 2;
        bool Stat = false;
        float time;
        int level = 1;

        virtual void update();
    protected:
        int movingDir;
    private:
};

#endif // GOOMBA_H
