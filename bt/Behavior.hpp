//
//  Behavior.hpp
//  GameBT
//
//  Created by River Liu on 15/1/2018.
//  Copyright © 2018 River Liu. All rights reserved.
//

#ifndef Behavior_hpp
#define Behavior_hpp

#include "Status.hpp"
#include <map>
#include <string>
#include <iostream>

class Blackboard;
namespace BT
{
    class Behavior
    {
    protected:
        Status m_eStatus;
        std::string m_sName;
        
    public:
        typedef std::map<std::string, std::string> BehaviorParams;
        typedef Behavior* (*createInstanceFn) (const BehaviorParams&);
        
    public:
        Behavior() : m_eStatus(Status::BH_INVALID), m_sName("Behavior") { }
		Behavior(const std::string& _name) : m_eStatus(Status::BH_INVALID), m_sName(_name) { }
        virtual ~Behavior() { }
        Status tick(Blackboard* _blackboard) /* single entry point for updating this behavior */
        {
			std::cout << m_sName << " tick" << std::endl;

            if (m_eStatus != Status::BH_RUNNING)
                onInitialize(_blackboard);
            
            onUpdate(_blackboard);
            
            if (m_eStatus != Status::BH_RUNNING)
                onTerminate(m_eStatus);
            
            return m_eStatus;
        }
        inline Status getStatus() { return m_eStatus; }
        inline bool isTerminated() const { return m_eStatus == Status::BH_SUCCESS || m_eStatus == Status::BH_FAILURE; } /* success or failed */
        inline void reset() { m_eStatus = Status::BH_INVALID; }
        inline void abort() { onTerminate(Status::BH_ABORTED); m_eStatus = Status::BH_ABORTED; }
        inline virtual void onInitialize(Blackboard* _blackboard) { }
        inline virtual Status onUpdate(Blackboard* _blackboard) { return m_eStatus; }
        inline virtual void onTerminate(Status _status) { }
        inline std::string getName() { return m_sName; }
        inline static Behavior* create(const BehaviorParams& _params) { return new Behavior; }
    };
}

#endif /* Behavior_hpp */
