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
		Root(const std::string& _name) : Decorator(_name) { }
        virtual ~Root() { }
        inline void setChild(Behavior* _child) { m_pChild = _child; }
		Status onUpdate(Blackboard* _blackboard)
		{
			m_pChild->tick(_blackboard);
			m_pChild->reset();
			return Status::BH_SUCCESS;
		}
		inline static Behavior* create(const BehaviorParams& _params)
		{
			auto it = _params.find("name");
			if (it != _params.end())
			{
				return new Root(it->second);
			}
			return new Root;
		}
    };
}

#endif /* Root_hpp */
