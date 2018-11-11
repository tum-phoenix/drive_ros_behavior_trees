#ifndef NODE_SWITCH_TO_RIGHT_LANE
#define NODE_SWITCH_TO_RIGHT_LANE

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

namespace NODES {
  class SwitchToRightLane : public BT::ActionNode {
  public:
      SwitchToRightLane(std::string name);
      void WaitForTick();
      void Halt() override;
  };
}


#endif
