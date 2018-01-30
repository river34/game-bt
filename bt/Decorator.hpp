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
        Decorator() : Behavior("Decorator") { }
		Decorator(const std::string& _name) : Behavior(_name) { }
        Decorator(Behavior* _child, const std::string& _name) : Behavior(_name), m_pChild(_child) { }
		Decorator(Behavior* _child) : Behavior("Decorator"), m_pChild(_child) { }
        virtual ~Decorator() { }
        inline void setChild(Behavior* _child) { m_pChild = _child; }
        inline static Behavior* create() { return new Decorator; }
    };
}

#endif /* Decorator_hpp */
