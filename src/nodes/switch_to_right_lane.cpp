/*
    --- Node description ---
    Used in: Obstacles
    Activation: Some kind of passing maneuver is finished
    Termination: car is on right lane
    Contains: switching to the right lane.
*/

#include <ros/ros.h>
#include <RCMode.h>
#include <nodes/switch_to_right_lane.h>
#include <string>

NODES::SwitchToRightLane::SwitchToRightLane(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&NODES::SwitchToRightLane::WaitForTick, this);
}

void NODES::SwitchToRightLane::WaitForTick()
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
              if(!latestMessage.command.compare("Switched to right lane")) {
                set_status(BT::SUCCESS);
                messageProcessed = true;
              }
            }
          }
          else {
            handleRCMode();
          }
        }
    }
}

void NODES::SwitchToRightLane::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
