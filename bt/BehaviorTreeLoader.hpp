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
        void loadBehaviorTree(const std::string& _file, BehaviorTree* _behaviorTree, BehaviorFactory* _behaviorFactory, const bool _isFilepath)
        {
			std::vector<char> buffer;

			if (_isFilepath == true)
			{
				std::ifstream theFile(_file);
				buffer = std::vector<char>((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
				std::cout << "Read filepath" << std::endl;
			}
			else
			{
				buffer = std::vector<char>(_file.begin(), _file.end());
				std::cout << "Read file as string" << std::endl;
			}
            buffer.push_back('\0');
            
            std::cout << "File size: " << buffer.size() << "\n";
            
            // parse the buffer using the xml file parsing library into doc
            xml_document<> doc;
            doc.parse<0>(&buffer[0]);
            
            std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";
            
            // find the root node
            xml_node<>* root_node = doc.first_node("BehaviorTree");
            
            // create root
            Behavior* root = _behaviorFactory->createInstance(root_node);
            assert (root != nullptr);
            std::cout << root->getName() << std::endl;

			// add root to behavior tree
			_behaviorTree->start(*root);
            
            // create behavior tree
            createNodes(_behaviorFactory, root, root_node);
        }
        
        void createNodes(BehaviorFactory* _behaviorFactory, Behavior* _behavior, xml_node<>* _node)
        {
            if (_node->first_node())
            {
                Composite* composite = dynamic_cast<Composite*>(_behavior);
                if (composite != nullptr)
                {
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
                
                Decorator* decorator = dynamic_cast<Decorator*>(_behavior);
                if (decorator != nullptr)
                {
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
