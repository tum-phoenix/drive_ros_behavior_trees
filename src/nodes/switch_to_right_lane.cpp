/*
    --- Node description ---
    Used in: Obstacles
    Activation: Some kind of passing maneuver is finished
    Termination: car is on right lane
    Contains: switching to the right lane.
*/

#include <ros/ros.h>
#include <nodes/switch_to_right_lane.h>
#include <string>

NODE_SWITCH_TO_RIGHT_LANE::SwitchToRightLane::SwitchToRightLane(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&SwitchToRightLane::WaitForTick, this);
}

void SwitchToRightLane::WaitForTick()
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
    }
}

void SwitchToRightLane::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
