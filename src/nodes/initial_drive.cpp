/*
    --- Node description ---
    Used in: Obstacles, Parking
    Activation: On system startup
    Termination: Crossing of chequered start line
    Contains: Driving straight forward, waiting for start line
*/

#include <ros/ros.h>
#include <nodes/initial_drive.h>
#include <string>

NODE_INITIAL_DRIVE::InitialDrive::InitialDrive(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&InitialDrive::WaitForTick, this);
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
        while (get_status() != BT::HALTED && get_status() != BT::SUCCESS)
        {
          if(!RCenabled) {
            /* General actions */
            if(!messageProcessed) {
              /* Action when message is received */
              set_status(BT::SUCCESS);
              messageProcessed = true;
            }
          }
          else {
            //Handle RC mode
          }
        }
    }
}

void InitialDrive::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    ROS_INFO("HALT");
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
