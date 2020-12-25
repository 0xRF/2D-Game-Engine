#pragma once

#include "../objects/object.hh"
class Component
{
public:

private:
    Object* self;
    virtual void OnActive();
    virtual void OnDisable();
    virtual void OnComponentRemove();
    virtual void OnObjectCreate();
    virtual void OnObjectDestroy();
};