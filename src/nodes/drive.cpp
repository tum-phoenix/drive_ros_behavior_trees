/*
    --- Node description ---
    Used in: Parking
    Activation: (Parking completed) or (just left intersection)
    Termination: (Crossing of chequered start line, only if the car needs to park) or (entering intersection)
    Contains: Following the track
    Child nodes: -/-
*/

#include <nodes/drive.h>
#include <string>

NODE_DRIVE::Drive::Drive(std::string name):
  BT::ActionNode(name)
{
  thread_ = std::thread(&Drive::WaitForTick, this);
}


void Drive::start() {
    started = true;
    //Notify other controls: (adjust wheels to straight forward), start driving, wait for chequered line
}

void Drive::WaitForTick()
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
              if(!latestMessage.command.compare("Intersection detected")) {
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

void Drive::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}
