iCreate Assembler
=================

## Note: This has not been tested on an actual iCreate!

# Getting Started
On Windows, install MinGW-w64 or MinGW and then type `make`. This produces an `iCreate.exe`
file. The usage is `iCreate.exe input_file.asm`, which will produce an output as follows,
for example: `152 13 137 1 44 128 0 156 1 144 137 0 0 0 0`. These numbers represent each
byte of the instruction sequence which can be sent to the iCreate through serial.

# Syntax
The syntax is generally `<instruction> <arg1> <arg2> <...>`. Follow the guide
[here](http://www.irobot.com/hrd_right_rail/create_rr/create_fam/createFam_rr_manuals.html)
on page 22 to get the instructions and their intended arguments. The instructions
map one to one:

```
start         Start
baud          Baud
control       Control
safe          Safe
full          Full
spot          Spot
cover         Cover
demo          Demo
drive         Drive
lsd           Low Side Drivers
led           LEDs
song          Song
play          Play
sensors       Sensors
cad           Cover and Dock
plsd          PWM Low Side Drivers
drivedir      Drive Direct
digout        Digital Outputs
stream        Stream
qlist         Query List
togglestrm    Pause/Resume Stream
sendir        Send IR
script        Script
playscript    Play Script
showscript    Show Script
waittime      Wait Time
waitdist      Wait Distance
waitangle     Wait Angle
waitevent     Wait Event
```

> Note! Using the script command has special syntax. Look in the examples/scripts directory
> to see exactly how to use the script command.

# TODO
* output to file in binary
* argument handling on integer bounds for all instructions
