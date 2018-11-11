#ifndef NODE_DRIVE
#define NODE_DRIVE

#include "action_node.h"
#include "drive_ros_behavior_trees/BehaviorTreeMessage.h"

extern drive_ros_behavior_trees::BehaviorTreeMessage latestMessage;
extern bool messageProcessed;
extern bool RCenabled;

namespace NODES {
  class Drive : public BT::ActionNode {
  private:
      bool started;
  public:
      Drive(std::string name);
      void start();
      void WaitForTick();
      void Halt() override;
  };
}


#endif
