#ifndef NODE_INTERSECTION_CROSSING
#define NODE_INTERSECTION_CROSSING

#include "action_node.h"

extern bool RCenabled;

class IntersectionCrossing : public BT::ActionNode {
public:
    IntersectionCrossing(std::string name);
    void start();
    void WaitForTick();
    void Halt() override;
};

#endif
