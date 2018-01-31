//
//  Root.hpp
//  GameBT
//
//  Created by River Liu on 22/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Single entry point.
//

#ifndef Root_hpp
#define Root_hpp

#include "Decorator.hpp"

namespace BT
{
    class Root : public Decorator
    {
    public:
        Root() : Decorator("Root") { }
        virtual ~Root() { }
        inline void setChild(Behavior* _child) { m_pChild = _child; }
		Status onUpdate(Blackboard* _blackboard)
		{
			m_pChild->tick(_blackboard);
			m_pChild->reset();
			return Status::BH_RUNNING;
		}
        inline static Behavior* create(const BehaviorParams& _params) { return new Root; }
    };
}

#endif /* Root_hpp */
