#ifndef NODE_CROSS_INTERSECTION
#define NODE_CROSS_INTERSECTION

#include "action_node.h"

extern bool RCenabled;

class CrossIntersection : public BT::ActionNode {
private:
    bool started;
public:
    CrossIntersection(std::string name);
   ~CrossIntersection();
    void start();
    void WaitForTick();
    void Halt() override;
};

#endif
