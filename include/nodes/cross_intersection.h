#ifndef NODE_CROSS_INTERSECTION
#define NODE_CROSS_INTERSECTION

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

namespace NODES {
  class CrossIntersection : public BT::ActionNode {
  public:
      CrossIntersection(std::string name);
     ~CrossIntersection();
      void start();
      void WaitForTick();
      void Halt() override;
  };
}


#endif
