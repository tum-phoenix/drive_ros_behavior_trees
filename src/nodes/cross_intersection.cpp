/*
    --- Node description ---
    Used in: Obstacles, Parking
    Activation: Entering intersection
    Termination: Left and right lane marking immediately upfront (->leaving intersection)
    Contains: Driving straight forward
*/

#include <ros/ros.h>
#include <RCMode.h>
#include <nodes/cross_intersection.h>
#include <string>

NODES::CrossIntersection::CrossIntersection(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&NODES::CrossIntersection::WaitForTick, this);
}

void NODES::CrossIntersection::WaitForTick()
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
              if(!latestMessage.command.compare("Intersection ended")) {
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

void NODES::CrossIntersection::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
