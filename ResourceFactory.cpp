#include "ResourceFactory.h"

#include <iostream>

using std::cout;
using std::endl;

ResourceFactory::ResourceFactory()
{
    cout<<"ResourceFactory::ResourceFactory()"<<endl;
}

ResourceFactory::~ResourceFactory()
{
    cout<<"ResourceFactory::~ResourceFactory()"<<endl;
    for (map<const char*, Texture2D*>::iterator i = textures.begin();
        i!=textures.end(); ++i)
            delete (i->second);
}

Texture2D* ResourceFactory::load(const char* fname)
{
    Texture2D* t = textures[fname];
    if (t==NULL)
        t = textures[fname] = new Texture2D(fname);
    return t;
}
