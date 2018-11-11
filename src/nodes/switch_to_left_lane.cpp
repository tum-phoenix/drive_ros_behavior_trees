/*
    --- Node description ---
    Used in: Obstacles
    Activation: Some kind of passing maneuver
    Termination: Car is on left lane
    Contains: switching the lane.
*/

#include <ros/ros.h>
#include <nodes/switch_to_left_lane.h>
#include <string>

NODES::SwitchToLeftLane::SwitchToLeftLane(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&NODES::SwitchToLeftLane::WaitForTick, this);
}

void NODES::SwitchToLeftLane::WaitForTick()
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
              if(!latestMessage.command.compare("Switched to left lane")) {
                set_status(BT::SUCCESS);
                messageProcessed = true;
              }
            }
          }
          else {
            //Handle RC mode
          }
        }
    }
}

void NODES::SwitchToLeftLane::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
