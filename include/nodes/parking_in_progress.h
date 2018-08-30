#ifndef NODE_PARKING_IN_PROGRESS
#define NODE_PARKING_IN_PROGRESS

#include "action_node.h"

class ParkingInProgress : public BT::ActionNode {
public:
    ParkingInProgress(std::string name);
    void WaitForTick();
//    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
