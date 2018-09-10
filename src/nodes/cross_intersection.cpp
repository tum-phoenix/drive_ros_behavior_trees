/*
    --- Node description ---
    Used in: Obstacles, Parking
    Activation: Entering intersection
    Termination: Left and right lane marking immediately upfront (->leaving intersection)
    Contains: Driving straight forward
*/

#include <ros/ros.h>
#include <nodes/cross_intersection.h>
#include <string>

NODE_CROSS_INTERSECTION::CrossIntersection::CrossIntersection(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&CrossIntersection::WaitForTick, this);
}

void CrossIntersection::WaitForTick()
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

void CrossIntersection::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
