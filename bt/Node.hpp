//
//  Node.hpp
//  GameBT
//
//  Created by River Liu on 16/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <vector>

namespace BT
{
    class Task;
    class Node
    {
    public:
        virtual Task* create() = 0;
        virtual ~Node() { }
        virtual void destroy(Task*) = 0;
    };
    typedef std::vector<Node> Nodes;
}

#endif /* Node_hpp */
