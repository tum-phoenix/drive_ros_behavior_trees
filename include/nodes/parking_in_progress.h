#ifndef NODE_PARKING_IN_PROGRESS
#define NODE_PARKING_IN_PROGRESS

#include "action_node.h"

extern bool RCenabled;

class ParkingInProgress : public BT::ActionNode {
public:
    ParkingInProgress(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
