#ifndef NODE_PARKING_SPOT_SEARCH
#define NODE_PARKING_SPOT_SEARCH

#include "action_node.h"

extern bool RCenabled;

class ParkingSpotSearch : public BT::ActionNode {
public:
    ParkingSpotSearch(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
