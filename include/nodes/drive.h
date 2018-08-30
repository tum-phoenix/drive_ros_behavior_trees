#ifndef NODE_DRIVE
#define NODE_DRIVE

#include "action_node.h"

class Drive : public BT::ActionNode {
private:
    bool started;
public:
    Drive(std::string name);
   ~Drive();
    void start();
    void WaitForTick();
//    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
