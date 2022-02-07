#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <iostream>
#include <list>

using std::list;
using std::cout;
using std::endl;

class Component
{
public:
    Component():deleted(false), active(true) {}
    virtual ~Component() {}
    virtual void update() = 0;
    virtual void draw() = 0;
    int health = 3;

    virtual void kill() { deleted = true; }
    virtual bool isActive() { return active; }

    friend class ComponentManager;
protected:
    bool deleted, active;
};

class ComponentManager
{
    public:
        void add(Component *);
        void update();
        void draw();
        void clear();

        template <class ComponentType> int count();
        template <class ComponentType> void find();
        template <class ComponentType> ComponentType* next();

        static ComponentManager &get()
        {
            static ComponentManager instance;
            return instance;
        }
    protected:
        list<Component*> components;
        list<Component*>:: iterator foundIter;
    private:
        ComponentManager() { cout<<"ComponentManager::ComponentManager()"<<endl; }
        ComponentManager(ComponentManager const &);
        void operator=(ComponentManager const &);
        ~ComponentManager() { cout<<"ComponentManager::~ComponentManager()"<<endl; clear(); }
};

template <class ComponentType> int ComponentManager::count()
{
    int cnt = 0;
    for (list<Component*>::iterator i = components.begin();
        i!=components.end(); ++i)
        {
            if ( dynamic_cast<ComponentType*>(*i) != NULL )
                ++cnt;
        }
    return cnt;
}

template <class ComponentType> void ComponentManager::find()
{
    foundIter = components.begin();
}

template <class ComponentType> ComponentType* ComponentManager::next()
{
    while ( foundIter != components.end() )
    {
        ComponentType *et = dynamic_cast<ComponentType*>(*foundIter);
        ++foundIter;
        if ( et != NULL )
            return et;
    }
    return NULL;
}

#endif // COMPONENTMANAGER_H
