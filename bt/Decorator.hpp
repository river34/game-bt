//
//  Decorator.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Decorator contains only one child.
// 

#ifndef Decorator_h
#define Decorator_h

#include "Behavior.hpp"

namespace BT
{
    class Decorator : public Behavior
    {
    protected:
        Behavior* m_pChild;
        
    public:
        Decorator() { }
        Decorator(Behavior* _child) : m_pChild(_child) { }
        virtual ~Decorator() { }
    };
}

#endif /* Decorator_h */
