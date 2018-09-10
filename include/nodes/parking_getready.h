#ifndef NODE_PARKING_GETREADY
#define NODE_PARKING_GETREADY

#include "action_node.h"

extern bool RCenabled;

class ParkingGetready : public BT::ActionNode {
public:
    ParkingGetready(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
