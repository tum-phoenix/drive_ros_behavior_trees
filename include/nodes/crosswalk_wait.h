#ifndef NODE_CROSSWALK_WAIT
#define NODE_CROSSWALK_WAIT

#include "action_node.h"

extern bool RCenabled;

class CrosswalkWait : public BT::ActionNode {
public:
    CrosswalkWait(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
