#ifndef NODE_CROSSWALK_WAIT
#define NODE_CROSSWALK_WAIT

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

class CrosswalkWait : public BT::ActionNode {
public:
    CrosswalkWait(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
