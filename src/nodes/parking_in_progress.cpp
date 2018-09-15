/*
    --- Node description ---
    Used in: Parking
    Activation: Car is ready to start parking
    Termination: Parking failed / Car is in parking spot according to selected technique
    Contains: Applying the predefined parking technique (parallel or perpendicular -> specific instructions)
*/

#include <ros/ros.h>
#include <nodes/parking_in_progress.h>
#include <string>

NODE_PARKING_IN_PROGRESS::ParkingInProgress::ParkingInProgress(std::string name) : ActionNode::ActionNode(name)
{
    thread_ = std::thread(&ParkingInProgress::WaitForTick, this);
}



void ParkingInProgress::WaitForTick()
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
              messageProcessed = true;
            }
          }
          else {
            //Handle RC mode
          }
        }

        ROS_INFO("Parking successful");
        //Increment successful parking counter
    }
}

void ParkingInProgress::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
