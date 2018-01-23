//
//  Repeater.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  RepeatDecorator is a Decorator that executes it child
//      until a limit is reached.
//      if the child fails, the decorator fails;
//      if the child succeeds, it is executed again in the same
//      update after the reset.

#ifndef Repeat_h
#define Repeat_h

#include "Decorator.hpp"

namespace BT
{
    class Repeater : public Decorator
    {
    private:
        unsigned int m_iCounter;
        unsigned int m_iLimit;
        
    public:
        Repeater() { }
        Repeater(unsigned int _limit) : m_iLimit(_limit) { }
        Repeater(Behavior* _child, unsigned int _limit) : Decorator(_child), m_iLimit(_limit) { }
        virtual ~Repeater() { }
        inline void onInitialize() { m_iCounter = 0; }
        inline void setLimit(unsigned int _limit) { m_iLimit = _limit; }
        inline void setChild(Behavior* _child) { m_pChild = _child; }
        Status onUpdate()
        {
            for (;;)
            {
                m_pChild->tick();
                if (m_pChild->getStatus() == Status::BH_RUNNING) break;
                if (m_pChild->getStatus() == Status::BH_FAILURE) return Status::BH_FAILURE;
                if (++m_iCounter == m_iLimit) return Status::BH_SUCCESS;
                m_pChild->reset();
            }
            return Status::BH_INVALID;
        }
        inline static Behavior* create() { return new Repeater; }
    };
}


#endif /* Repeat_h */