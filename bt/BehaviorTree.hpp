//
//  BehaviorTree.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef BehaviorTree_h
#define BehaviorTree_h

#include <deque>
#include "Behavior.hpp"

namespace BT
{
    class BehaviorTree
    {
    protected:
        std::deque<Behavior*> m_Behaviors;
        
    public:
        void start(Behavior& bh)
        {
            m_Behaviors.push_front(&bh);
        }
        
        void tick()
        {
            // Insert an end-of-update marker into the list of tasks.
            m_Behaviors.push_back(nullptr);
            
            // Keep going updating tasks until we encounter the marker.
            while (step())
            {
                continue;
            }
        }
        
        bool step()
        {
            Behavior* current = m_Behaviors.front();
            m_Behaviors.pop_front();
            
            // If this is the end-of-update marker, stop processing.
            if (current == nullptr)
            {
                return false;
            }
            
            // Perform the update on this individual task.
            current->tick();
            
            // drop it into the queue for the next tick().
            if (current->getStatus() == Status::BH_RUNNING)
            {
                m_Behaviors.push_back(current);
            }
            return true;
        }
    };
}

#endif /* BehaviorTree_h */
