#ifndef NODE_PARKING_GETREADY
#define NODE_PARKING_GETREADY

#include "action_node.h"

class ParkingGetready : public BT::ActionNode {
public:
    ParkingGetready(std::string name);
    void WaitForTick();
//    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
