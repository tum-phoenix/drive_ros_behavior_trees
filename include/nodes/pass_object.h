#ifndef NODE_PASS_OBJECT
#define NODE_PASS_OBJECT

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

namespace NODES {
  class PassObject : public BT::ActionNode {
  public:
      PassObject(std::string name);
      void WaitForTick();
      void Halt() override;
  };
}


#endif
