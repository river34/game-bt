//
//  Shared.hpp
//  GameBT
//
//  Created by River Liu on 16/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Shared_H
#define Shared_H

#include <assert.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1600) // VS2010
#define ASSERT(X) assert(X); __analysis_assume(X)
#define ASSERT_MSG(X, M) ASSERT(X)
#else
#define ASSERT(X) assert(X)
#define ASSERT_MSG(X, M) ASSERT(X)
#endif

#endif // SHARED_H