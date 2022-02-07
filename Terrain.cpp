#include "Terrain.h"

#include <windows.h>

#include <gl/gl.h>

#include <fstream>
#include <iostream>

using std::ios;
using std::fstream;
using std::string;
using std::cout;
using std::endl;

#include "Power.h"
#include "fire.h"
#include "fireone.h"
#include "Ret.h"
#include "PortalT.h"
#include "Portal.h"
#include "Mario.h"
#include "Luigi.h"
#include "Coin.h"
#include "Sky.h"
#include "Chimeny.h"
#include "Goomba.h"
#include "ResourceFactory.h"

Terrain::Terrain()
    :tile({
          Sprite(ResourceFactory::get().load("floor.bmp"),1,1)
          }),
    fname(NULL), sizeX(0), sizeY(0), tiles(NULL)
{
    cout<<"Terrain::Terrain()"<<endl;
}

Terrain::~Terrain()
{
    cout<<"Terrain::~Terrain()"<<endl;
}

void Terrain::die(int e)
{
    cout<<"Level '"<<fname<<"' loading error: "<<e<<endl;
    exit(EXIT_FAILURE);
}

void Terrain::create(const char *fname)
{
    if (tiles!=NULL)
        delete[] tiles;
    this->fname = fname;

    fstream ifs(fname, ios::in);
    if (!ifs.is_open())
        die(1);
    ifs>>sizeX;
    ifs>>sizeY;
    if (sizeX<=0 || sizeY<=0)
        die(11);
    tiles = new char[sizeX * sizeY];
    for (int i=sizeY-1; i>=0; --i)
    {
        if (ifs.eof())
            die(12);
        string buf;
        ifs>>buf;
        if ((int)buf.size()!=sizeX)
            die(13);
        strncpy( &tiles[i*sizeX], buf.c_str(), sizeX );
    }
    Luigi* player = new Luigi(Sprite(ResourceFactory::get().load("luigi.bmp"), 8, 8), float2(0,0), 0);
    Mario* player1 = new Mario(Sprite(ResourceFactory::get().load("mario.bmp"), 8, 8), float2(0,0), 0);
    for (int y=0; y<sizeY; ++y)
        for (int x=0; x<sizeX; ++x)
    {
        switch (tiles[x+y*sizeX])
        {
        case 'M':
            tiles[x+y*sizeX] = '.';
            player1->setPosition(float2(x,y));
            ComponentManager::get().add(player1);
            break;
        case 'L':
            tiles[x+y*sizeX] = '.';
            player->setPosition(float2(x,y));
            ComponentManager::get().add(player);
            break;
        case 'c':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Coin(Sprite(ResourceFactory::get().load("coin.bmp")), float2(x,y), 0.f));
            break;
////        case '#':
////            break;
        case 'g':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Goomba(Sprite(ResourceFactory::get().load("goomba.bmp"),15,15), float2(x,y), 0.f));
            break;
        case 'T':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Goomba(Sprite(ResourceFactory::get().load("turtle.bmp"),15,15), float2(x,y), 0.f));
            break;
        case 'f':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new fire(Sprite(ResourceFactory::get().load("firek.bmp"),2,2), float2(-11,1), 0.f));
            break;
        case 'F':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new fireone(Sprite(ResourceFactory::get().load("fireonek.bmp"),2,2), float2(-10,1), 0.f));
            break;
        case 'S':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Sky(Sprite(ResourceFactory::get().load("Sky.bmp"),1,1), float2(x,y), 0.f));
            break;
        case 'H':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Chimeny(Sprite(ResourceFactory::get().load("ChimenyD.bmp"),1,1), float2(x,y), 0.f));
            ComponentManager::get().add(new Ret(float2(x,y), 0, float2(x, y)));
            break;
         case 'h':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Chimeny(Sprite(ResourceFactory::get().load("ChimenyU.bmp"),1,1), float2(x,y), 0.f));
            ComponentManager::get().add(new Ret(float2(x,y), 0, float2(x, y)));
            break;
        case '>':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new PortalT(float2(x,y), 0, float2(x+26.f, y)));
            break;
        case '<':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Portal(float2(x,y), 0, float2(x-26.f, y)));
            break;
        case ')':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Chimeny(Sprite(ResourceFactory::get().load("ChimenyD.bmp"),1,1), float2(x,y), 0.f));
            ComponentManager::get().add(new Portal(float2(x,y), 0, float2(x-26.f, y)));
            break;
        case '(':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Chimeny(Sprite(ResourceFactory::get().load("ChimenyD.bmp"),1,1), float2(x,y), 0.f));
            ComponentManager::get().add(new PortalT(float2(x,y), 0, float2(x+26.f, y)));
            break;
         case '}':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Chimeny(Sprite(ResourceFactory::get().load("ChimenyU.bmp"),1,1), float2(x,y), 0.f));
            ComponentManager::get().add(new Portal(float2(x,y), 0, float2(x-26.f, y)));
            break;
        case '{':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Chimeny(Sprite(ResourceFactory::get().load("ChimenyU.bmp"),1,1), float2(x,y), 0.f));
            ComponentManager::get().add(new PortalT(float2(x,y), 0, float2(x+26.f, y)));
            break;
        case 'P':
            tiles[x+y*sizeX] = '.';
            ComponentManager::get().add(new Power(Sprite(ResourceFactory::get().load("Power.bmp"),3,3), float2(x,y), 0.f));
            break;

        }
    }
    ifs.close();
}

void Terrain::draw()
{
    glTranslatef(-viewPos.x + 2.8f, -viewPos.y, 0);
    for (int y = 0; y < sizeY; ++y)
    {
        for (int x = 0; x < sizeX; ++x)
        {
            switch ( tiles[x+y*sizeX] )
            {
            case '#': tile[0].draw(float2(x,y)); break;
            }
        }
    }
}

float2 Terrain::collisionWith(char tileType, float2 p, float2 size)
{
    int x1=lroundf(p.x-.5f);
    int y1=lroundf(p.y-.5f);
    int x2=x1+1;
    int y2=y1+1;
    float left = x1 + .5f - ( p.x - size.x );
    if (left<0.f) left=0.f;
    float right = p.x + size.x - ( x2 - .5f );
    if (right<0.f) right=0.f;
    float bottom = y1 + .5f - ( p.y - size.y );
    if (bottom<0.f) bottom=0.f;
    float top = p.y + size.y - ( y2 - .5f );
    if (top<0.f) top=0.f;
    unsigned char mask = 0; // y2  2  3  4 8
                            // y1  0  1  1 2
                            //    x1 x2
    if ( x1==-1 || y1==-1 || tiles[x1+y1*sizeX] == tileType)
        mask |= 0x01;
    if ( x1==-1 || y2==sizeY || tiles[x1+y2*sizeX] == tileType)
        mask |= 0x04;
    if ( x2==sizeX || y1==-1 || tiles[x2+y1*sizeX] == tileType)
        mask |= 0x02;
    if ( x2==sizeX || y2==sizeY || tiles[x2+y2*sizeX] == tileType)
        mask |= 0x08;
    float2 r;
    switch (mask)
    {
    case 0: // .
    case 15:
        break;
    case 1: // /^
        if (left < bottom)
            r.x = left;
        else
            r.y = bottom;
        break;
    case 7: // /^
        r = float2(left, bottom);
        break;
    case 2: // ^\ _
        if (right < bottom)
            r.x = -right;
        else
            r.y = bottom;
        break;
    case 11:
        r = float2(-right, bottom);
        break;
    case 4: // \.
        if (left < top)
            r.x = left;
        else
            r.y = -top;
        break;
    case 13:
        r = float2(left, -top);
        break;
    case 8: // ./
        if (right < top)
            r.x = -right;
        else
            r.y = -top;
        break;
    case 14:
        r = float2( -right, -top );
        break;
    case 3: // ^
        r.y = bottom;
        break;
    case 12: // v
        r.y = -top;
        break;
    case 5: // >
        r.x = left;
        break;
    case 10: // <
        r.x = -right;
        break;
    case 6: // ./^
        if (left + bottom < right + top)
            r = float2( left, bottom );
        else
            r = float2( -right, -top );
        break;
    case 9: // ^\.
        if (left + top < right + bottom)
            r = float2( left, -top );
        else
            r = float2( -right, bottom);
        break;
    }
    return r;
}

float2 Terrain::collisionWithNot(char tileType, float2 p, float2 size)
{
    int x1=lroundf(p.x-.5f);
    int y1=lroundf(p.y-.5f);
    int x2=x1+1;
    int y2=y1+1;
    float left = x1 + .5f - ( p.x - size.x );
    if (left<0.f) left=0.f;
    float right = p.x + size.x - ( x2 - .5f );
    if (right<0.f) right=0.f;
    float bottom = y1 + .5f - ( p.y - size.y );
    if (bottom<0.f) bottom=0.f;
    float top = p.y + size.y - ( y2 - .5f );
    if (top<0.f) top=0.f;
    unsigned char mask = 0; // y2  2  3  4 8
                            // y1  0  1  1 2
                            //    x1 x2
    if ( x1==-1 || y1==-1 || tiles[x1+y1*sizeX] != tileType)
        mask |= 0x01;
    if ( x1==-1 || y2==sizeY || tiles[x1+y2*sizeX] != tileType)
        mask |= 0x04;
    if ( x2==sizeX || y1==-1 || tiles[x2+y1*sizeX] != tileType)
        mask |= 0x02;
    if ( x2==sizeX || y2==sizeY || tiles[x2+y2*sizeX] != tileType)
        mask |= 0x08;
    float2 r;
    switch (mask)
    {
    case 0: // .
    case 15:
        break;
    case 1: // /^
        if (left < bottom)
            r.x = left;
        else
            r.y = bottom;
        break;
    case 7: // /^
        r = float2(left, bottom);
        break;
    case 2: // ^\ _
        if (right < bottom)
            r.x = -right;
        else
            r.y = bottom;
        break;
    case 11:
        r = float2(-right, bottom);
        break;
    case 4: // \.
        if (left < top)
            r.x = left;
        else
            r.y = -top;
        break;
    case 13:
        r = float2(left, -top);
        break;
    case 8: // ./
        if (right < top)
            r.x = -right;
        else
            r.y = -top;
        break;
    case 14:
        r = float2( -right, -top );
        break;
    case 3: // ^
        r.y = bottom;
        break;
    case 12: // v
        r.y = -top;
        break;
    case 5: // >
        r.x = left;
        break;
    case 10: // <
        r.x = -right;
        break;
    case 6: // ./^
        if (left + bottom < right + top)
            r = float2( left, bottom );
        else
            r = float2( -right, -top );
        break;
    case 9: // ^\.
        if (left + top < right + bottom)
            r = float2( left, -top );
        else
            r = float2( -right, bottom);
        break;
    }
    return r;
}

void Terrain::setViewPos(float2 _viewPos)
{
    viewPos = _viewPos;
    if (viewPos.x < sizeX)
        viewPos.x = sizeX - .5f;
    if (viewPos.x >= sizeX - halfViewSize.x)
        viewPos.x = sizeX - halfViewSize.x - 0.5f;
    if (viewPos.y < halfViewSize.y - .5f)
        viewPos.y = halfViewSize.y - .5f;
    if (viewPos.y > sizeY - halfViewSize.y - .5f)
        viewPos.y = sizeY - halfViewSize.y - .5f;
}
