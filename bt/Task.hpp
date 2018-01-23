//
//  Task.hpp
//  GameBT
//
//  Created by River Liu on 16/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Task_h
#define Task_h

#include "Status.hpp"

namespace BT
{
    class Node;
    class Task
    {
    protected:
        Node* m_pNode;
        
    public:
        Task(Node& _node) : m_pNode(&_node) { }
        virtual ~Task() {}
        virtual Status onUpdate() = 0;
        virtual void onInitialize() { }
        virtual void onTerminate(Status) { }
    };
}

#endif /* Task_h */
