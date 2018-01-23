//
//  ActiveSelector.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  ActiveSelector is a Selector that actively rechecks
//      its children.

#ifndef ActiveSelector_h
#define ActiveSelector_h

#include "Selector.hpp"

namespace BT
{
    class ActiveSelector : public Selector
    {
    public:
        virtual ~ActiveSelector() { }
        inline virtual void onInitialize() override { m_CurrentChild = m_Children.end(); }
        virtual Status onUpdate() override
        {
            auto prev = m_CurrentChild;
            Selector::onInitialize();
            Status result = Selector::onUpdate();
            if (prev != m_Children.end() && prev != m_CurrentChild)
            {
                abort();
            }
            return result;
        }
    };
}

#endif /* ActiveSelector_h */
