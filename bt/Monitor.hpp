//
//  Monitor.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Monitor is a Parallel that continuously checks
//      if conditions are valid. It has two children:
//      the fitst one contains conditions to be monitored;
//      the second one contains actions.

#ifndef Monitor_hpp
#define Monitor_hpp

#include "Parallel.hpp"

namespace BT
{
    class Monitor : public Parallel
    {
    public:
		Monitor() : Parallel(Parallel::PL_REQUIRE_ONE, Parallel::PL_REQUIRE_ONE, "Monitor") { }
		Monitor(const std::string& _name) : Parallel(Parallel::PL_REQUIRE_ONE, Parallel::PL_REQUIRE_ONE, _name) { }
        virtual ~Monitor() { }
        inline void addCondition(Behavior* condition) { m_Children.insert(m_Children.begin(), condition); }
        inline void addAction(Behavior* action) { m_Children.push_back(action); }
    };
}

#endif /* Monitor_hpp */
