/*
    --- Node description ---
    Used in: Obstacles
    Activation: Crosswalk detected and car velocity is 0
    Termination: All pedestrians crossed the road.
    Contains: Waiting
*/

#include <ros/ros.h>
#include <nodes/crosswalk_wait.h>
#include <string>

NODE_CROSSWALK_WAIT::CrosswalkWait::CrosswalkWait(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&CrosswalkWait::WaitForTick, this);
}

void CrosswalkWait::WaitForTick()
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

void CrosswalkWait::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
