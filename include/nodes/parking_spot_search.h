#ifndef NODE_PARKING_SPOT_SEARCH
#define NODE_PARKING_SPOT_SEARCH

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

namespace NODES {
  class ParkingSpotSearch : public BT::ActionNode {
  public:
      ParkingSpotSearch(std::string name);
      void WaitForTick();
      void Halt() override;
  };
}


#endif
