#include <windows.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>

#define Player Luigi
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::ostringstream;

#include "Sprite.h"

#include "Power.h"
#include "Luigi.h"
#include "Goomba.h"
#include "Mario.h"
#include "ComponentManager.h"
#include "ResourceFactory.h"
#include "Terrain.h"
#include "Coin.h"
#include "fire.h"
#include "SpriteText.h"

int screenWidth=770, screenHeight=450;

bool Pow = true;
int a=0;
int b=0;
std::string napis;
int pom1, pom2;

enum GameState
{
    PLAY, GAMEOVER, YOUWON, LEVELSTART, LEVELFINISHED
} gameState = LEVELSTART;

Sprite *gameOver;
Sprite *youWon;

SpriteText *levelStart;

int timeOut = ::GetTickCount()+3000;
int currentLevel = 1;
const int maxLevel = 3;

void end(void)
{
    cout<<"Game terminated"<<endl;
}

void renderScene(void) {
    glClearColor(.5f, .5f, .5f, .5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -1.f);
    glPushMatrix();
        Terrain::get().draw();
        ComponentManager::get().draw();
    glPopMatrix();
    switch (gameState)
    {
    case PLAY:
        levelStart->draw(float2(-13.f,7.5f), 0, 0.5f);
        break;
    case GAMEOVER:
        gameOver->draw(float2(0,0), 0.f, 16.f);
        break;
    case YOUWON:
        youWon->draw(float2(0,0), 0.f, 14.f);
        break;
    case LEVELSTART:
        levelStart->draw(float2(-8.5f,0.f), 0, 2.5f);
        break;
    }
    glutSwapBuffers();
}

void resize(int wid, int hei)
{
    screenWidth = wid;
    screenHeight = hei ? hei : 1;
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const float scale = 8.f;
    glOrtho(-scale*(float)wid/(float)hei*.98f, scale*(float)wid/(float)hei*.98f, -scale, scale, .1f, 10.f);
    glMatrixMode(GL_MODELVIEW);
}

void idle(void)
{
    Sleep(15);
    switch (gameState)
    {
    case PLAY:
        {
            ComponentManager::get().update();
            ComponentManager::get().find<Luigi>();
            Luigi *p = ComponentManager::get().next<Luigi>();
            ComponentManager::get().find<Mario>();
            Mario *q = ComponentManager::get().next<Mario>();
            if ( p==NULL && q==NULL )
            {
                gameState = GAMEOVER;
                timeOut = ::GetTickCount() + 4000;
            }
            else if (ComponentManager::get().count<Goomba>()==0)
            {
                gameState = LEVELFINISHED;
                timeOut = ::GetTickCount() + 4000;
            }


            ComponentManager::get().find<Goomba>();
            Goomba* goomba = ComponentManager::get().next<Goomba>();
            if (ComponentManager::get().count<Goomba>()==1)
                {
                    goomba->Speed();
                 }
            if (Pow)
            {
                ComponentManager::get().find<Coin>();
                Coin* coin = ComponentManager::get().next<Coin>();
                if (ComponentManager::get().count<Coin>()==0)
                    {
                        ComponentManager::get().find<Power>();
                        Power* power = ComponentManager::get().next<Power>();
                        if (ComponentManager::get().count<Power>() > 0)
                        {
                            power->Refresh();
                            Pow = false;
                        }
                       if (ComponentManager::get().count<Power>() == 0)
                       {
                           ComponentManager::get().add(new Power(Sprite(ResourceFactory::get().load("Power.bmp"),3,3), float2(12.5,9.5), 0.f));
                           Pow = false;
                       }

                     }
            }

             if ( q!=NULL )
             {
                 if (pom1 != q->money())
                 {
                    a = a + q->money();
                    pom1 = q->money();
                 }
             }
            if ( p!=NULL )
            {
                if (pom2 != p->money())
                {
                    b = b + p->money();
                    pom2 = p->money();
                }
            }

            napis = "asd";
            levelStart->setText("P1: ", a,"                 Level ", currentLevel,"                 P2: ", b);
        }
        break;
    case GAMEOVER:
        Pow = true;
        if (::GetTickCount() > timeOut)
        {

            ComponentManager::get().clear();
            if (currentLevel == 1)
            {
                Terrain::get().create("level1.txt");
                a=0;
                b=0;
            }
            if (currentLevel == 2)
            Terrain::get().create("level2.txt");
            if (currentLevel == 3)
            Terrain::get().create("level3.txt");
            if (currentLevel == 4)
            Terrain::get().create("level4.txt");
            timeOut = ::GetTickCount() + 3000;
            gameState = LEVELSTART;
            Luigi *p;
            Mario *q;
            ComponentManager::get().find<Luigi>();
            ComponentManager::get().find<Mario>();
            p = ComponentManager::get().next<Luigi>();
            q = ComponentManager::get().next<Mario>();
            if (p!=NULL)
                Terrain::get().setViewPos(p->getPosition());
            if (q!=NULL)
                Terrain::get().setViewPos(q->getPosition());
        }
        break;
    case LEVELFINISHED:
        Pow = true;
        ++currentLevel;
        if (currentLevel>maxLevel)
        {
            gameState = YOUWON;
            timeOut = ::GetTickCount() + 4000;
            currentLevel = 1;
            levelStart->setText("Level ", currentLevel);
        }
        else
        {
            ComponentManager::get().clear();
            ostringstream o;
            o<<"level"<<currentLevel<<".txt";
            Terrain::get().create(o.str().c_str());
            levelStart->setText("Level ", currentLevel);
            timeOut = ::GetTickCount() + 3000;
            gameState = LEVELSTART;
            Luigi *p;
            Mario *q;
            ComponentManager::get().find<Luigi>();
            ComponentManager::get().find<Mario>();
            p = ComponentManager::get().next<Luigi>();
            q = ComponentManager::get().next<Mario>();
            if (p!=NULL)
                Terrain::get().setViewPos(p->getPosition());
            if (q!=NULL)
                Terrain::get().setViewPos(q->getPosition());
        }
        break;
    case YOUWON:

        a=0;
        b=0;
        if (::GetTickCount() > timeOut)
        {
            ComponentManager::get().clear();
            Terrain::get().create("level1.txt");
            timeOut = ::GetTickCount() + 3000;
            gameState = LEVELSTART;
            currentLevel = 1;
            Luigi *p;
            Mario *q;
            ComponentManager::get().find<Luigi>();
            ComponentManager::get().find<Mario>();
            p = ComponentManager::get().next<Luigi>();
            q = ComponentManager::get().next<Mario>();
            if (p!=NULL)
                Terrain::get().setViewPos(p->getPosition());
            if (q!=NULL)
                Terrain::get().setViewPos(q->getPosition());
        }
        break;
    case LEVELSTART:
        levelStart->setText("Level ", currentLevel);
        if (::GetTickCount() > timeOut)
        {
            gameState = PLAY;
        }
        break;
    }
    glutPostRedisplay();
}

void keyb(unsigned char k, int x, int y)
{
    switch (k)
    {
    case 27:
        cout<<"Shutdown by Escape"<<endl;
        exit(EXIT_SUCCESS);
    }
    Mario *q;
    ComponentManager::get().find<Mario>();
    q = ComponentManager::get().next<Mario>();
    if (q!=NULL)
        q->keyb(k, true);
}

void keybUp(unsigned char k, int x, int y)
{
    Mario *q;
    ComponentManager::get().find<Mario>();
    q = ComponentManager::get().next<Mario>();
    if (q!=NULL)
        q->keyb(k, false);
}



void keyb1(int k, int, int) // funkcja callback wciśnięcia klawisza specjalnego
{
     switch (k)
    {
    case 27:
        cout<<"Shutdown by Escape"<<endl;
        exit(EXIT_SUCCESS);
    }
    Luigi *p;
    ComponentManager::get().find<Luigi>();
    p = ComponentManager::get().next<Luigi>();
    if (p!=NULL)
        p->keyb(k, true);
   }

void keybUp1(int k, int x, int y)
{
    Luigi *p;
    ComponentManager::get().find<Luigi>();
    p = ComponentManager::get().next<Luigi>();
    if (p!=NULL)
        p->keyb(k, false);
}

int main(int argc, char **argv) {
    cout<<"Initialization"<<endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(120, 140);
    glutInitWindowSize(screenWidth, screenHeight);
    glutCreateWindow("ARZ Game");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(resize);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyb);
    glutSpecialFunc(keyb1);
    glutKeyboardUpFunc(keybUp);
    glutSpecialUpFunc(keybUp1);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    Terrain::get().create("level1.txt");
    Terrain::get().setViewSize(float2(21, 16));
    Luigi *p;
    Mario *q;
    ComponentManager::get().find<Luigi>();
    ComponentManager::get().find<Mario>();
    p = ComponentManager::get().next<Luigi>();
    q = ComponentManager::get().next<Mario>();
    if (p!=NULL)
        Terrain::get().setViewPos(p->getPosition());
    else if (q!=NULL)
        Terrain::get().setViewPos(q->getPosition());

    gameOver = new Sprite(ResourceFactory::get().load("gameover.bmp"));
    youWon = new Sprite(ResourceFactory::get().load("youwon.bmp"));

    levelStart = new SpriteText(Sprite(ResourceFactory::get().load("font.bmp"), 128));
    levelStart->setText("Level ", currentLevel);

    atexit(end);
    cout<<"Game started"<<endl;

    glutMainLoop();
}
