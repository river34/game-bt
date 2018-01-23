//
//  Behavior.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Behavior_h
#define Behavior_h

#include "Status.hpp"

namespace BT
{
    class Behavior
    {
    protected:
        Status m_eStatus;
        
    public:
        Behavior() : m_eStatus(Status::BH_INVALID) { }
        virtual ~Behavior() { m_eStatus = Status::BH_INVALID; }
        Status tick() /* single entry point for updating this behavior */
        {
            if (m_eStatus == Status::BH_INVALID)
                onInitialize();
            
            onUpdate();
            
            if (m_eStatus != Status::BH_RUNNING)
                onTerminate(m_eStatus);
            
            return m_eStatus;
        }
        inline Status getStatus() { return m_eStatus; }
        inline bool isTerminated() const { return m_eStatus == Status::BH_SUCCESS || m_eStatus == Status::BH_FAILURE; } /* success or failed */
        inline void reset() { m_eStatus = Status::BH_INVALID; }
        inline void abort() { onTerminate(Status::BH_ABORTED); m_eStatus = Status::BH_ABORTED; }
        inline virtual void onInitialize() { }
        inline virtual Status onUpdate() { return m_eStatus; }
        inline virtual void onTerminate(Status _status) { }
    };
}

#endif /* Behavior_h */
