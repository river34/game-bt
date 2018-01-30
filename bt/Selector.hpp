//
//  Selector.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Selector is a Composite that executes each child behavior in order
//      until it finds a child that either succeeds or keeps running.
// 

#ifndef Selector_hpp
#define Selector_hpp

#include "Composite.hpp"

namespace BT
{
    class Selector : public Composite
    {
    public:
        Selector() { m_sName = "Selector"; }
        virtual ~Selector() { }
        virtual Status onUpdate() override
        {
            while(true)
            {
                Status status = (*m_CurrentChild)->tick();
                // if child succeeds or keeps running
                if (status != Status::BH_FAILURE) return status;
                // if all children have executed
                if (++m_CurrentChild == m_Children.end()) return Status::BH_FAILURE;
            }
            return Status::BH_INVALID;
        }
    };
}


#endif /* Selector_hpp */
