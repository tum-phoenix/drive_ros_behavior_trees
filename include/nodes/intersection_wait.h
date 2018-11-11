#ifndef NODE_INTERSECTION_WAIT
#define NODE_INTERSECTION_WAIT

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

namespace NODES {
  class IntersectionWait : public BT::ActionNode {
  public:
      IntersectionWait(std::string name);
      void WaitForTick();
      void Halt() override;
  };
}


#endif
