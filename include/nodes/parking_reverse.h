#ifndef NODE_PARKING_REVERSE
#define NODE_PARKING_REVERSE

#include "action_node.h"

class ParkingReverse : public BT::ActionNode {
public:
    ParkingReverse(std::string name);
    void WaitForTick();
//    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
