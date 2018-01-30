//
//  BehaviorTreeLoader.hpp
//  GameBT
//
//  Created by River Liu on 16/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef BehaviorTreeLoader_hpp
#define BehaviorTreeLoader_hpp

#include <stdio.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "Behavior.hpp"
#include "Decorator.hpp"
#include "Repeater.hpp"
#include "Composite.hpp"
#include "Sequence.hpp"
#include "Filter.hpp"
#include "Selector.hpp"
#include "ActiveSelector.hpp"
#include "Parallel.hpp"
#include "Monitor.hpp"
#include "Root.hpp"
#include "BehaviorTree.hpp"
#include "BehaviorFactory.hpp"
#include "../rapidxml/rapidxml.hpp"

using namespace rapidxml;
namespace BT
{
    class BehaviorTreeLoader
    {
    public:
        BehaviorTree* loadBehaviorTree(const std::string& _filepath)
        {
            std::ifstream theFile ("BTTest2.xml");
            assert (theFile.is_open());
            
            std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
            buffer.push_back('\0');
            
            std::cout << "File size: " << buffer.size() << "\n";
            
            // parse the buffer using the xml file parsing library into doc
            xml_document<> doc;
            doc.parse<0>(&buffer[0]);
            
            std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
            
            // find the root node
            xml_node<>* root_node = doc.first_node("BehaviorTree");
            
            // create factory
            BehaviorFactory* behaviorFactory = new BehaviorFactory;
            behaviorFactory->registerClass("Repeater", &Repeater::create);
            behaviorFactory->registerClass("Sequence", &Sequence::create);
            behaviorFactory->registerClass("ActiveSelector", &ActiveSelector::create);
            behaviorFactory->registerClass("BehaviorTree", &Root::create);
            behaviorFactory->registerClass("Action", &Behavior::create);
            behaviorFactory->registerClass("Condition", &Behavior::create);
            
            // create tree
            BehaviorTree* bt = new BehaviorTree;
            
            // create root
            Behavior* root = behaviorFactory->createInstance(root_node);
            assert (root != nullptr);
            std::cout << root->getName() << std::endl;
            
            // create behavior tree
            createNodes(behaviorFactory, root, root_node);
            
            return bt;
        }
        
        void createNodes(BehaviorFactory* _behaviorFactory, Behavior* _behavior, xml_node<>* _node)
        {
            if (_node->first_node())
            {
                Composite* composite = (Composite*)_behavior;
                if (composite != nullptr)
                {
                    std::cout << "It is a composite" << std::endl;
                    // for each child, add to the composite
                    for (xml_node<>* node = _node->first_node(); node; node = node->next_sibling())
                    {
                        Behavior* child = _behaviorFactory->createInstance(node);
                        assert (child != nullptr);
                        composite->addChild(child);
                        std::cout << child->getName() << std::endl;
                        createNodes(_behaviorFactory, child, node);
                    }
                }
                
                Decorator* decorator = (Decorator*)_behavior;
                if (decorator != nullptr)
                {
                    std::cout << "It is a decorator" << std::endl;
                    // add child to the decorator
                    xml_node<>* node = _node->first_node();
                    Behavior* child = _behaviorFactory->createInstance(node);
                    assert (child != nullptr);
                    decorator->setChild(child);
                    std::cout << child->getName() << std::endl;
                    createNodes(_behaviorFactory, child, node);
                }
            }
        }
    };
}

#endif /* BehaviorTreeLoader_hpp */
