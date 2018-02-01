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
        Selector() : Composite("Selector") { }
		Selector(const std::string& _name) : Composite(_name) { }
        virtual ~Selector() { }
		virtual void onInitialize(Blackboard* _blackboard) { m_CurrentChild = m_Children.begin(); }
        virtual Status onUpdate(Blackboard* _blackboard) override
        {
			// Keep going until a child behavior says its running
			for (;;)
            {
                Status status = (*m_CurrentChild)->tick(_blackboard);

				if (status == Status::BH_FAILURE) std::cout << (*m_CurrentChild)->getName() << " in Selector BH_FAILURE" << std::endl;
				if (status == Status::BH_SUCCESS) std::cout << (*m_CurrentChild)->getName() << " in Selector BH_SUCCESS" << std::endl;
				if (status == Status::BH_ABORTED) std::cout << (*m_CurrentChild)->getName() << " in Selector BH_ABORTED" << std::endl;
				if (status == Status::BH_INVALID) std::cout << (*m_CurrentChild)->getName() << " in Selector BH_INVALID" << std::endl;

                // if child succeeds or keeps running
                if (status != Status::BH_FAILURE) { return status; }

                // if all children have executed
                if (++m_CurrentChild == m_Children.end()) { return Status::BH_FAILURE; }
            }
        }
		inline static Behavior* create(const BehaviorParams& _params) { return new Selector; }
    };
}


#endif /* Selector_hpp */
