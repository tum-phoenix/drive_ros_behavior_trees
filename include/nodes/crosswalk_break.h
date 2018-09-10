#ifndef NODE_CROSSWALK_BREAK
#define NODE_CROSSWALK_BREAK

#include "action_node.h"

extern bool RCenabled;

class CrosswalkBreak : public BT::ActionNode {
public:
    CrosswalkBreak(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
