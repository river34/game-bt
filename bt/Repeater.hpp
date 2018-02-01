//
//  Repeater.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  RepeatDecorator is a Decorator that executes it child
//      until a limit is reached.
//      if the child fails, the decorator fails;
//      if the child succeeds, it is executed again in the same
//      update after the reset.

#ifndef Repeat_hpp
#define Repeat_hpp

#include "Decorator.hpp"
#include <sstream>

namespace BT
{
    class Repeater : public Decorator
    {
    private:
        unsigned int m_iCounter;
        unsigned int m_iLimit;
        
    public:
		Repeater() : Decorator("Repeater") { }
		Repeater(const std::string& _name) : Decorator(_name) { }
		Repeater(unsigned int _limit, const std::string& _name) : Decorator(_name), m_iLimit(_limit) { }
		Repeater(unsigned int _limit) : Decorator("Repeater"), m_iLimit(_limit) { }
        Repeater(Behavior* _child, unsigned int _limit, const std::string& _name) : Decorator(_child, _name), m_iLimit(_limit) { }
		Repeater(Behavior* _child, unsigned int _limit) : Decorator(_child, "Repeater"), m_iLimit(_limit) { }
        virtual ~Repeater() { }
        inline void onInitialize() { m_iCounter = 0; }
        inline void setLimit(unsigned int _limit) { m_iLimit = _limit; }
        inline void setChild(Behavior* _child) { m_pChild = _child; }
        Status onUpdate(Blackboard* _blackboard)
        {
            for (;;)
            {
                m_pChild->tick(_blackboard);
                if (m_pChild->getStatus() == Status::BH_RUNNING) break;
                if (m_pChild->getStatus() == Status::BH_FAILURE) { return Status::BH_FAILURE; }
                if (++m_iCounter == m_iLimit) { return Status::BH_SUCCESS; }
                m_pChild->reset();
            }
			return Status::BH_INVALID;
        }
        inline static Behavior* create(const BehaviorParams& _params)
        {
			unsigned int limit = 1;
            auto it = _params.find("limit");
            if (it != _params.end())
            {
                std::stringstream s(it->second);
                s >> limit;
            }
			return new Repeater(limit);
        }
    };
}


#endif /* Repeat_hpp */
