#ifndef NODE_PARKING_SPOT_SEARCH
#define NODE_PARKING_SPOT_SEARCH

#include "actionNode.h"

class ParkingSpotSearch : public BTAction {
public:
    ParkingSpotSearch(std::string name);
    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
