//
//  Composite.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Composite contains amultiple children.
// 

#ifndef Composite_h
#define Composite_h

#include <vector>
#include "Behavior.hpp"

namespace BT
{
    class Composite : public Behavior
    {
    protected:
        typedef std::vector<Behavior*> Behaviors;
        Behaviors m_Children;
        Behaviors::iterator m_CurrentChild;
        
    public:
        virtual ~Composite() { }
        inline void addChild(Behavior* _child) { m_Children.push_back(_child); }
        inline void removeChild(Behavior* _child) { auto it = std::find(m_Children.begin(), m_Children.end(), _child);
            if (it != m_Children.end()) {std::swap(*it, m_Children.back()); m_Children.pop_back();} }
        void clearChildern() { m_Children.clear(); }
        inline virtual void onInitialize() override { m_CurrentChild = m_Children.begin(); }
    };
}

#endif /* Composite_h */
