#ifndef NODE_PARKING_IN_PROGRESS
#define NODE_PARKING_IN_PROGRESS

#include "actionNode.h"

class ParkingInProgress : public BTAction {
public:
    ParkingInProgress(std::string name);
    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
