//
//  ActiveSelector.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  ActiveSelector is a Selector that actively rechecks
//      its children.

#ifndef ActiveSelector_hpp
#define ActiveSelector_hpp

#include "Selector.hpp"

namespace BT
{
    class ActiveSelector : public Selector
    {
    public:
        ActiveSelector() : Selector("ActiveSelector") { }
		ActiveSelector(const std::string& _name) : Selector(_name) { }
        virtual ~ActiveSelector() { }
        inline virtual void onInitialize(Blackboard* _blackboard) override { m_CurrentChild = m_Children.end(); }
        virtual Status onUpdate(Blackboard* _blackboard) override
        {
            auto prev = m_CurrentChild;
            Selector::onInitialize(_blackboard);
            Status status = Selector::onUpdate(_blackboard);
            if (prev != m_Children.end() && prev != m_CurrentChild)
            {
				(*prev)->abort();
            }
			return status;
        }
        inline static Behavior* create(const BehaviorParams& _params) { return new ActiveSelector; }
    };
}

#endif /* ActiveSelector_hpp */
