/*
    --- Node description ---
    Used in: Obstacles
    Activation: Crosswalk detected
    Termination: Car velocity is 0
    Contains: Breaking while following the track
*/

#include <ros/ros.h>
#include <nodes/crosswalk_break.h>
#include <string>

NODES::CrosswalkBreak::CrosswalkBreak(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&NODES::CrosswalkBreak::WaitForTick, this);
}

void NODES::CrosswalkBreak::WaitForTick()
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
              if(!latestMessage.command.compare("Car stopped")) {
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

void NODES::CrosswalkBreak::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
