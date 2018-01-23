//
//  Sequence.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Sequence is a Composite that executes each child behavior in sequence
//      until all children have executed successfully, or
//      until one child behavior fails.
//

#ifndef Sequence_h
#define Sequence_h

#include "Composite.hpp"

namespace BT
{
    class Sequence : public Composite
    {
    public:
        virtual ~Sequence() { }
        virtual Status onUpdate() override
        {
            while(true)
            {
                Status status = (*m_CurrentChild)->tick();
                // if one child behavior fails
                if (status != Status::BH_SUCCESS) return status;
                // if all children have executed successfully
                if (++m_CurrentChild == m_Children.end()) return Status::BH_SUCCESS;
            }
            return Status::BH_INVALID;
        }
        inline static Behavior* create() { return new Sequence; }
    };
}

#endif /* Sequence_h */
