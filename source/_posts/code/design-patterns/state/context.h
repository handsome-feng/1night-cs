/**
 * 定义当前状态
 */
#ifndef CONTEXT_H
#define CONTEXT_H

#include "state.h"

class Context
{
public:
   Context();
   virtual ~Context();

   void changeState(State *st);
   void request();
private:
   State *m_pState;
};

#endif