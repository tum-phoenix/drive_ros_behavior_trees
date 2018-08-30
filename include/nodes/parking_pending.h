#ifndef NODE_PARKING_PENDING
#define NODE_PARKING_PENDING

#include "actionNode.h"

class ParkingPending : public BTAction {
public:
    ParkingPending(std::string name);
    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
