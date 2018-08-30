/*
    --- Node description ---
    Used in: Parking
    Activation: Parking completed
    Termination: Crossing of chequered start line, only if the car needs to park
    Contains: Driving the track
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

        while (get_status() != BT::HALTED)
        {
  /*HERE THE CODE TO EXECUTE FOR THE ACTION.
   wHEN THE ACTION HAS FINISHED CORRECLTY, CALL set_status(BT::SUCCESS)
  IF THE ACTION FAILS, CALL set_status(BT::FAILURE)*/
        }
    }
}

void Drive::Halt()
{
    /*HERE THE CODE TO PERFORM WHEN THE ACTION IS HALTED*/
    set_status(BT::HALTED);
    DEBUG_STDOUT("HALTED state set!");
}

BT::ReturnStatus Drive::Tick() {
  return BT::EXIT;
}

int Drive::DrawType() {
  return BT::ACTION;
}
