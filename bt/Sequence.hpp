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

#ifndef Sequence_hpp
#define Sequence_hpp

#include "Composite.hpp"

namespace BT
{
    class Sequence : public Composite
    {
    public:
        Sequence() : Composite("Sequence") { }
		Sequence(const std::string& _name) : Composite(_name) { }
        virtual ~Sequence() { }
        virtual Status onUpdate(Blackboard* _blackboard) override
        {
			for (;;)
            {
                Status status = (*m_CurrentChild)->tick(_blackboard);

                // if one child behavior fails
				if (status != Status::BH_SUCCESS) { return status; }
                // if all children have executed successfully
                if (++m_CurrentChild == m_Children.end()) { return Status::BH_SUCCESS; }
            }
			return Status::BH_FAILURE;
        }
        inline static Behavior* create(const BehaviorParams& _params) 
		{
			auto it = _params.find("name");
			if (it != _params.end())
			{
				return new Sequence(it->second);
			}
			return new Sequence; 
		}
    };
}

#endif /* Sequence_hpp */
