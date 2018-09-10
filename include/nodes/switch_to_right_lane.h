#ifndef NODE_SWITCH_TO_RIGHT_LANE
#define NODE_SWITCH_TO_RIGHT_LANE

#include "action_node.h"

extern bool RCenabled;

class SwitchToRightLane : public BT::ActionNode {
public:
    SwitchToRightLane(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
