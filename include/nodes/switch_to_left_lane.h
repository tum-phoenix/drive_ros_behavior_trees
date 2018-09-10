#ifndef NODE_SWITCH_TO_LEFT_LANE
#define NODE_SWITCH_TO_LEFT_LANE

#include "action_node.h"

extern bool RCenabled;

class SwitchToLeftLane : public BT::ActionNode {
public:
    SwitchToLeftLane(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
