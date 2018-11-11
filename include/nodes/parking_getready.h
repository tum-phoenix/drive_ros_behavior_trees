#ifndef NODE_PARKING_GETREADY
#define NODE_PARKING_GETREADY

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

namespace NODES {
  class ParkingGetready : public BT::ActionNode {
  public:
      ParkingGetready(std::string name);
      void WaitForTick();
      void Halt() override;
  };
}


#endif
