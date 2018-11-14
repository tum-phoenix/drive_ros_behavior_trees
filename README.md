# Behavior Trees
Behavior trees implementation of the drive team. 

Still work in progress!!

## WTF are Behavior Trees?!
Behavior Trees can be used for anything from modeling and supervising the current status of the car to a complete control unit taking in processed sensor data and outputting motor commands.

Basically they are trees organizing the possible states of some machine. They use Control Nodes (Sequence nodes, Fallback nodes, Parallel nodes -> usually provided by the lib you use) which specify the way their children are executed, and Action Nodes (-> usually custom coded) which specify how an atomar task is performed. 

All nodes have a a state for themselves (idle, running, success, ...). Of course, a control node can have both control and action nodes as children, while action nodes never have children. For further reading I recommend Chapter 1 of the Manual provided by the library I used (see "Dependencies").

## Current functions and abilities of the trees
For now, the BT models are capable of
- Displaying the current status of the car
- Executing high-level control, such as when to start driving, when to start looking for a parking spot, etc. (actual command implementation still WIP)

And they cannot
- Give low-level motor commands (imo they are not meant to do that..?)
- Display RC mode, although RC mode is being handled by the node. It's only unnecessarily complex to implement that into the BT models.
- Handle *all* kinds of failure states (e.g. out of track, parking not successful, ...).
- Provide the currently important street signs, especially not the priority road sign (I think they should at some point be able to do that).
- Provide their current status via a ROS service (yet). This is still to be done.

## Messages needed in topic "behavior_tree_topic" to control the BT
This table is meant to try and standardize the message contents some nodes send to update the BT. I decided to go with plain trext since it's just as powerful as using ID numbers or something else, but they can be immediately read in the console output if needed. I tried coming up with easily understandable and unambiguous short messages. For now, it doesn't seem necessary to me to include anything additionally to the notification command in the message, this may change during development.

**TODO:** If you know the responsible package for some event, please exchange the (?) with its name.

Note: These lists are way from final; expect changes to be made, specifically regarding something being in the topic or in the service list.

Driving Mode (Parking/Obstacles) | Event  / To be transmitted | Message Content | Proposed source package
--- | --- | --- | ---
Both | RC mode enabeled/disabeled | "Toggle RC mode" | remote control receiver...
Both | Start line crossed | "Crossed start line" | drive_ros_image_recognition
Parking | Fitting parking spot found | "Parking spot found" | (?) Lidar...
Parking | Car is on track again (reverse parking successful) | "Parking process completed" | move_base
Parking | Intersection immediately upfront | "Intersection detected" | drive_ros_marker_detection
Parking | Intersection is over, lane markings left and right directly in front of the car | "Intersection ended" | (?)
Obstacles | Static lane blocking object immediately upfront | "Static lane blocking object detected" | (?)
Obstacles | Barred area immediately upfront | "Barred area detected" | drive_ros_marker_detection
Obstacles | Dynamic object detected | "Dynamic object detected" | (?)
Obstacles | Crosswalk immediately upfront | "Crosswalk detected" | drive_ros_marker_detection
Obstacles | Intersection immediately upfront | "Intersection detected" | drive_ros_marker_detection
Obstacles | Car switched to left lane, is on track | "Switched to left lane" | CommonRoad
Obstacles | Car switched to right lane, is on track | "Switched to right lane" | CommonRoad
Obstacles | The relative position of the obstacle to the right (while on left lane, avoiding it) | "Object/Barred area on the right", (int) position | drive_ros_marker_detection
Obstacles | The positions of pedestrians at a crosswalk / Only whether all have crossed the street? | *not clear yet, message format!* | (?)

## Services needed for info-calls by the BT
Driving Mode (Parking/Obstacles) | Brief content | srv-file | Proposed source package
--- | --- | --- | ---
Both | current vehicle velocity | VelocityService.src | move_base


Annotation: "Immediately upfront" always means the point of time when acting is required. E.g. when a crosswalk is detected, the car may still drive towards it, but when it's immediately upfront, breaking is required.

## BT Model Graphs
The two behavior trees for parking and obstacles mode can be found in the two corresponding files ("/parkingModeGraph", "/obstaclesModeGraph") in this repo. They are in GRAPHVIZ-format and can be visualized using websites like http://www.webgraphviz.com/. They are meant for better understanding of the code structure, and some details are being left out.

## Dependencies
* [ROS behavior tree library](https://github.com/miccol/ROS-Behavior-Tree) Note: For a more meaningful console output comment out line 44 in tree_node.h ("#define DEBUG")
