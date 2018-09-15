#ifndef NODE_FOLLOWING_OBJECT
#define NODE_FOLLOWING_OBJECT

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

class FollowingObject : public BT::ActionNode {
public:
    FollowingObject(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
