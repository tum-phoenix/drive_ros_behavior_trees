#ifndef NODE_INTERSECTION_CROSSING
#define NODE_INTERSECTION_CROSSING

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

namespace NODES {
  class IntersectionCrossing : public BT::ActionNode {
  public:
      IntersectionCrossing(std::string name);
      void start();
      void WaitForTick();
      void Halt() override;
  };
}


#endif
