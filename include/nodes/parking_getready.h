#ifndef NODE_PARKING_GETREADY
#define NODE_PARKING_GETREADY

#include "actionNode.h"

class ParkingGetready : public BTAction {
public:
    ParkingGetready(std::string name);
    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
