#ifndef NODE_PASS_BARRED_AREA
#define NODE_PASS_BARRED_AREA

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

class PassBarredArea : public BT::ActionNode {
public:
    PassBarredArea(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
