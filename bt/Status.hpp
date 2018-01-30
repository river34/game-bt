//
//  Status.hpp
//  GameBT
//
//  Created by River Liu on 16/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Status_hpp
#define Status_hpp

namespace BT
{
    enum class Status /* return values for behaviors */
    {
        BH_INVALID,
        BH_SUCCESS,
        BH_FAILURE,
        BH_RUNNING,
        BH_ABORTED,
    };
}

#endif /* Status_hpp */
