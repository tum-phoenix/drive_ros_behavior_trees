/*
    --- Node description ---
    Used in: Obstacles
    Activation: Waiting at the intersection is over or the car has the right of way
    Termination: The car is on track again.
    Contains: Crossing the intersection
*/

#include <ros/ros.h>
#include <nodes/intersection_crossing.h>
#include <string>

NODES::IntersectionCrossing::IntersectionCrossing(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&NODES::IntersectionCrossing::WaitForTick, this);
}

void NODES::IntersectionCrossing::WaitForTick()
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

void NODES::IntersectionCrossing::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
