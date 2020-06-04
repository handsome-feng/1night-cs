#ifndef STATE_H
#define STATE_H

class Context;

class State
{
public:
    virtual void handle(Context *context) = 0;
};

#endif