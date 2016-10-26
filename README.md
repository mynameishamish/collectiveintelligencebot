# Collective Intelligence System
## Fork of @nikmart's Interaction Engine framework

Basic set up is:

Stepper's -> Arduino -> Pi -> Node.JS -> Wifi (GroupInteraction) -> Laptop

Web page button is pushed (html) ->
JS (client.js) funtion called ->
Server.js logs activation and pushes character to Pi Serial Port ->
Arduino registers character and triggers behavior







To run this example:

1. clone the repo
2. upload the `helloYouSketch.ino` to your Arduino
3. run `node server.js /dev/ttyACM0` using node (make sure your Arduino port is correct)


More info here: https://github.com/nikmart/interaction-engine/wiki




Notes:

To connect Arduino to Kinect, one potential way is to run Arduino on same laptop as Kinect, use Visual Studio to push character to serial port, then Arduino will register serial port character and trigger behavior, bypassing the Pi and Node.js (not ideal but could be done to get things up and running)
