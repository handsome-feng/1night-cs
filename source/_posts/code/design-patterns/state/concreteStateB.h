#ifndef CONCRETE_STATE_B_H
#define CONCRETE_STATE_B_H

#include "state.h"

class ConcreteStateB : public State
{
public:
    ConcreteStateB();
    virtual ~ConcreteStateB();
    static State *Instance();
    void handle(Context *c);

private:
    static State *m_pState;
};

#endif
