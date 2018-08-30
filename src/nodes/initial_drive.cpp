/*
    --- Node description ---
    Used in: Obstacles, Parking
    Activation: On system startup
    Termination: Crossing of chequered start line
    Contains: Driving straight forward, waiting for start line
    Child nodes: -/-
*/

#include <ros/ros.h>
#include <nodes/initial_drive.h>
#include <string>

NODE_INITIAL_DRIVE::InitialDrive::InitialDrive(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&InitialDrive::WaitForTick, this);
}


void InitialDrive::start() {
    started = true;
    //Notify other controls: (adjust wheels to straight forward), start driving, wait for chequered line
}

void InitialDrive::WaitForTick()
{
    while (true)
    {
        // Waiting for the first tick to come
        DEBUG_STDOUT(get_name() << " WAIT FOR TICK");

        tick_engine.Wait();
        DEBUG_STDOUT(get_name() << " TICK RECEIVED");

        // Running state
        set_status(BT::RUNNING);
        // Perform action...

        while (get_status() != BT::HALTED)
        {
  /*HERE THE CODE TO EXECUTE FOR THE ACTION.
   wHEN THE ACTION HAS FINISHED CORRECLTY, CALL set_status(BT::SUCCESS)
  IF THE ACTION FAILS, CALL set_status(BT::FAILURE)*/

        }
    }
}

void InitialDrive::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}

BT::ReturnStatus InitialDrive::Tick() {
  return BT::EXIT;
}

int InitialDrive::DrawType() {
  return BT::ACTION;
}
/*
void InitialDrive::execute_callback(const behavior_tree_core::BTGoalConstPtr& ptr) {

}
*/
