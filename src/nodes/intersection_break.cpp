/*
    --- Node description ---
    Used in: Obstacles
    Activation: Intersection detected
    Termination: Car velocity is 0
    Contains: Breaking and following the track.
*/

#include <ros/ros.h>
#include <nodes/intersection_break.h>
#include <string>

NODES::IntersectionBreak::IntersectionBreak(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&NODES::IntersectionBreak::WaitForTick, this);
}

void NODES::IntersectionBreak::WaitForTick()
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

void NODES::IntersectionBreak::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
