#ifndef NODE_INTERSECTION_WAIT
#define NODE_INTERSECTION_WAIT

#include "action_node.h"

extern bool RCenabled;

class IntersectionWait : public BT::ActionNode {
public:
    IntersectionWait(std::string name);
    void WaitForTick();
    void Halt() override;
};

#endif
