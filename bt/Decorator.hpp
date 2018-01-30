//
//  Decorator.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Decorator contains only one child.
// 

#ifndef Decorator_hpp
#define Decorator_hpp

#include "Behavior.hpp"

namespace BT
{
    class Decorator : public Behavior
    {
    protected:
        Behavior* m_pChild;
        
    public:
        Decorator() { m_sName = "Decorator"; }
        Decorator(Behavior* _child) : m_pChild(_child) { m_sName = "Decorator"; }
        virtual ~Decorator() { }
        inline void setChild(Behavior* _child) { m_pChild = _child; }
        inline static Behavior* create() { return new Decorator; }
    };
}

#endif /* Decorator_hpp */
