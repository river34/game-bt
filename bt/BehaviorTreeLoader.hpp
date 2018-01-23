//
//  BehaviorTreeLoader.hpp
//  GameBT
//
//  Created by River Liu on 16/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef BehaviorTreeLoader_h
#define BehaviorTreeLoader_h

#include "Behavior.hpp"
#include "Decorator.hpp"
#include "Repeater.hpp"
#include "Composite.hpp"
#include "Sequence.hpp"
#include "Filter.hpp"
#include "Selector.hpp"
#include "ActiveSelector.hpp"
#include "Parallel.hpp"
#include "Monitor.hpp"
#include "BehaviorTree.hpp"
#include "../rapidxml/rapidxml.hpp"

namespace BT
{
    class BehaviorTreeLoader
    {
    public:
        BehaviorTree* loadBehaviorTree(const std::string& _filepath) const
        {
            BehaviorTree* bt = new BehaviorTree;
            
            
            
            return bt;
        }
    };
}

#endif /* BehaviorTreeLoader_h */
