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
