#ifndef NODE_INTERSECTION_BREAK
#define NODE_INTERSECTION_BREAK

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

class IntersectionBreak : public BT::ActionNode {
public:
    IntersectionBreak(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
