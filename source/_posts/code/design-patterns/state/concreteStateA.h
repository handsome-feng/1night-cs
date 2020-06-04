#ifndef CONCRETE_STATE_A_H
#define CONCRETE_STATE_A_H

#include "state.h"

class ConcreteStateA : public State
{
public:
    ConcreteStateA();
    virtual ~ConcreteStateA();
    static State *Instance();
    void handle(Context *c);

private:
    static State *m_pState;
};

#endif