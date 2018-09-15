#ifndef NODE_SWITCH_TO_LEFT_LANE
#define NODE_SWITCH_TO_LEFT_LANE

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

class SwitchToLeftLane : public BT::ActionNode {
public:
    SwitchToLeftLane(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
