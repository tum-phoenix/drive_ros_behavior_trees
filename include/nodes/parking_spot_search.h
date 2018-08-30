#ifndef NODE_PARKING_SPOT_SEARCH
#define NODE_PARKING_SPOT_SEARCH

#include "action_node.h"

class ParkingSpotSearch : public BT::ActionNode {
public:
    ParkingSpotSearch(std::string name);
    void WaitForTick();
//    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
