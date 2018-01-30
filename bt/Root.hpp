//
//  Decorator.hpp
//  GameBT
//
//  Created by River Liu on 22/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Decorator contains only one child.
//

#ifndef Root_hpp
#define Root_hpp

#include "Decorator.hpp"

namespace BT
{
    class Root : public Decorator
    {
    public:
        Root() { m_sName = "Root"; }
        virtual ~Root() { }
        inline void setChild(Behavior* _child) { m_pChild = _child; }
        inline static Behavior* create(const BehaviorParams& _params) { return new Root; }
    };
}

#endif /* Root_hpp */
