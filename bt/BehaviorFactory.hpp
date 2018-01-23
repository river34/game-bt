//
//  BehaviorFactory.hpp
//  GameBT
//
//  Created by River Liu on 16/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef BehaviorFactory_h
#define BehaviorFactory_h

#include <tuple>
#include <iostream>
#include <string>
#include <map>
#include "Behavior.hpp"
#include "Decorator.hpp"
#include "Repeater.hpp"
#include "Sequence.hpp"
#include "Filter.hpp"
#include "ActiveSelector.hpp"
#include "Parallel.hpp"
#include "rapidxml/rapidxml.hpp"

namespace BT
{
    class BehaviorFactory
    {
    private:
        BehaviorFactory(const BehaviorFactory&) {}
        BehaviorFactory& operator=(const BehaviorFactory&) { return *this; }
        typedef std::map<std::string, Behavior::createInstanceFn> FactoryMap;
        FactoryMap m_FactoryMap;
        
    public:
        BehaviorFactory()
        {
            registerClass("Repeater", &Repeater::create);
            registerClass("Sequence", &Sequence::create);
            registerClass("ActiveSelector", &ActiveSelector::create);
            registerClass("Condition", &Filter::create);
        }
        ~BehaviorFactory() { }
        void registerClass(const std::string& name, Behavior::createInstanceFn pfnCreate)
        {
            m_FactoryMap[name] = pfnCreate;
        }
        Behavior* createInstance(const rapidxml::xml_node<>* node)
        {
            FactoryMap::iterator it = m_FactoryMap.find(node->name());
            if (it != m_FactoryMap.end())
            {
                return it->second();
            }
            return nullptr;
        }
    };
}

#endif /* BehaviorFactory_h */
