//
//  BehaviorFactory.hpp
//  GameBT
//
//  Created by River Liu on 16/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef BehaviorFactory_hpp
#define BehaviorFactory_hpp

#include <tuple>
#include <iostream>
#include <string>
#include <map>
#include "Behavior.hpp"
#include "../rapidxml/rapidxml.hpp"

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
        BehaviorFactory() { }
        ~BehaviorFactory() { m_FactoryMap.clear(); }
        void registerClass(const std::string& name, Behavior::createInstanceFn pfnCreate)
        {
            m_FactoryMap[name] = pfnCreate;
        }
        Behavior* createInstance(const rapidxml::xml_node<>* node)
        {
			std::string id = (node->first_attribute("id") == nullptr) ? "" : node->first_attribute("id")->value();
			std::string name = node->name();
            FactoryMap::iterator it = m_FactoryMap.find(id + name);
            Behavior::BehaviorParams params = Behavior::BehaviorParams();
            for (rapidxml::xml_attribute<>* attr = node->first_attribute(); attr; attr = attr->next_attribute()) {
                if (strcmp(attr->name(), "name")) continue;
                params[attr->name()] = attr->value();
            }
            if (it != m_FactoryMap.end())
            {
                return it->second(params);
            }
            return nullptr;
        }
    };
}

#endif /* BehaviorFactory_hpp */
