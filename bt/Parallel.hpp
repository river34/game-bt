//
//  Parallel.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//
//  Parallel is a Composite that executes all children at the same time.
//  

#ifndef Parallel_hpp
#define Parallel_hpp

#include "Composite.hpp"

namespace BT
{
    class Parallel : public Composite
    {
    public:
        enum Policy
        {
            PL_REQUIRE_ONE,
            PL_REQUIRE_ALL,
        };
        
    private:
        Policy m_eSuccessPolicy;
        Policy m_eFailurePolicy;
        
    public:
        Parallel(Policy _success, Policy _failure) : m_eSuccessPolicy(_success), m_eFailurePolicy(_failure) { m_sName = "Repeater"; }
        virtual ~Parallel() { }
        virtual Status onUpdate() override
        {
            unsigned int iSuccessCount = 0, iFailureCount = 0;
            for (auto it: m_Children)
            {
                Behavior* behavior = it;
                if (behavior->isTerminated() == false) behavior->tick();
                if (behavior->getStatus() == Status::BH_SUCCESS)
                {
                    iSuccessCount ++;
                    if (m_eSuccessPolicy == PL_REQUIRE_ONE) return Status::BH_SUCCESS;
                }
                if (behavior->getStatus() == Status::BH_FAILURE)
                {
                    iFailureCount ++;
                    if (m_eSuccessPolicy == PL_REQUIRE_ONE) return Status::BH_FAILURE;
                }
            }
            if (m_eSuccessPolicy == PL_REQUIRE_ALL && iSuccessCount == m_Children.size()) return Status::BH_SUCCESS;
            if (m_eFailurePolicy == PL_REQUIRE_ALL && iFailureCount == m_Children.size()) return Status::BH_FAILURE;
            return Status::BH_RUNNING;
        }
        virtual void onTerminate(Status _statues) override /* immediately terminates all running children */
        {
            for (auto it: m_Children)
            {
                Behavior* behavior = it;
                if (behavior->getStatus() == Status::BH_RUNNING) behavior->abort();
            }
        }
    };
}

#endif /* Parallel_hpp */
