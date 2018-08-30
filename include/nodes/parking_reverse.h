#ifndef NODE_PARKING_REVERSE
#define NODE_PARKING_REVERSE

#include "actionNode.h"

class ParkingReverse : public BTAction {
public:
    ParkingReverse(std::string name);
    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
