#ifndef NODE_CROSSWALK_BREAK
#define NODE_CROSSWALK_BREAK

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

namespace NODES {
  class CrosswalkBreak : public BT::ActionNode {
  public:
      CrosswalkBreak(std::string name);
      void WaitForTick();
      void Halt() override;
  };
}


#endif
