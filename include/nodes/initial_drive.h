#ifndef NODE_INITIAL_DRIVE
#define NODE_INITIAL_DRIVE

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

class InitialDrive : public BT::ActionNode {
public:
    InitialDrive(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
