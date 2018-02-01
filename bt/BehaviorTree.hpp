//
//  BehaviorTree.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef BehaviorTree_hpp
#define BehaviorTree_hpp

#include <deque>
#include "Behavior.hpp"

namespace BT
{
    class BehaviorTree
    {
    protected:
		Behavior* m_pRoot;
        std::deque<Behavior*> m_Behaviors;
        
    public:
        void setRoot(Behavior& _root)
        {
			m_pRoot = &_root;
        }
        
        void tick(Blackboard* _blackboard)
        {
			// Insert root.
			m_Behaviors.push_front(m_pRoot);

            // Insert an end-of-update marker into the list of tasks.
            m_Behaviors.push_back(nullptr);
            
            // Keep going updating tasks until we encounter the marker.
            while (step(_blackboard))
            {
                continue;
            }
        }
        
        bool step(Blackboard* _blackboard)
        {
            Behavior* current = m_Behaviors.front();
            m_Behaviors.pop_front();
            
            // If this is the end-of-update marker, stop processing.
            if (current == nullptr)
            {
                return false;
            }
            
            // Perform the update on this individual task.
            current->tick(_blackboard);
            
            // drop it into the queue for the next tick().
            if (current->getStatus() == Status::BH_RUNNING)
            {
                m_Behaviors.push_back(current);
				std::cout << "push_back = " << current->getName() << std::endl;
            }
			std::cout << "m_Behaviors = " << m_Behaviors.size() << std::endl;
            return true;
        }
    };
}

#endif /* BehaviorTree_hpp */
