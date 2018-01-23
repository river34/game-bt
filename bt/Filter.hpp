//
//  Filter.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Filter is a Sequence with a single condition and a single action.
//

#ifndef Filter_h
#define Filter_h

#include "Sequence.hpp"

namespace BT
{
    class Filter : public Sequence
    {
    public:
        virtual ~Filter() { }
        inline void addCondition(Behavior* condition) { m_Children.insert(m_Children.begin(), condition); }
        inline void addAction(Behavior* action) { m_Children.push_back(action); }
    };
}

#endif /* Filter_h */
