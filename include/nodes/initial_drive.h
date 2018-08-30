#ifndef NODE_INITIAL_DRIVE
#define NODE_INITIAL_DRIVE

#include "action_node.h"

class InitialDrive : public BT::ActionNode {
private:
    bool started;
public:
    InitialDrive(std::string name);
   ~InitialDrive();
    void start();
    void WaitForTick();
//    void execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) override;
    void Halt() override;
    int DrawType() override;
    BT::ReturnStatus Tick() override;
};

#endif
