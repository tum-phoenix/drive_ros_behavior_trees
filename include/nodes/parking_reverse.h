#ifndef NODE_PARKING_REVERSE
#define NODE_PARKING_REVERSE

#include "action_node.h"

extern bool RCenabled;

class ParkingReverse : public BT::ActionNode {
public:
    ParkingReverse(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
