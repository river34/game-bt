//
//  Filter.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Filter is a Sequence with a single condition and a single action.
//

#ifndef Filter_hpp
#define Filter_hpp

#include "Sequence.hpp"

namespace BT
{
    class Filter : public Sequence
    {
    public:
        Filter() { m_sName = "Filter"; }
        virtual ~Filter() { }
        inline void addCondition(Behavior* condition) { m_Children.insert(m_Children.begin(), condition); }
        inline void addAction(Behavior* action) { m_Children.push_back(action); }
        inline static Behavior* create(const BehaviorParams& _params) { return new Filter; }
    };
}

#endif /* Filter_hpp */
