#ifndef NODE_PARKING_REVERSE
#define NODE_PARKING_REVERSE

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

namespace NODES {
  class ParkingReverse : public BT::ActionNode {
  public:
      ParkingReverse(std::string name);
      void WaitForTick();
      void Halt() override;
  };
}


#endif
