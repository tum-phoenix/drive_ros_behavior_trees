/*
    --- Node description ---
    Used in: Obstacles
    Activation: Intersection detected and car velocity is 0
    Termination: Minimum waiting time is over or another car crossed the intersection
    Contains: Waiting.
*/

#include <ros/ros.h>
#include <nodes/intersection_wait.h>
#include <string>

NODE_INTERSECTION_WAIT::IntersectionWait::IntersectionWait(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&IntersectionWait::WaitForTick, this);
}

void IntersectionWait::WaitForTick()
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

void IntersectionWait::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
