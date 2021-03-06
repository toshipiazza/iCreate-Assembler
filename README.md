iCreate Assembler
=================

## Note: This has not been tested on an actual iCreate!

# Getting Started
On Windows, install MinGW-w64 or MinGW and then type `make`. This produces an `iCreate.exe`
file. The usage is `iCreate.exe input_file.asm`, which will produce an output as follows,
for example: `152 13 137 1 44 128 0 156 1 144 137 0 0 0 0`. These numbers represent each
byte of the instruction sequence which can be sent to the iCreate through serial.

Alternatively you can use CMake to build the project.

# Syntax
The syntax is generally `<instruction> <arg1> <arg2> <...>`. Follow the guide
[here](http://www.irobot.com/filelibrary/pdfs/hrd/create/Create%20Open%20Interface_v2.pdf)
on page 22 to get the instructions and their intended arguments. The instructions
map one to one:

```
start         Start                       drivedir      Drive Direct
baud          Baud                        digout        Digital Outputs
control       Control                     stream        Stream
safe          Safe                        qlist         Query List
full          Full                        togglestrm    Pause/Resume Stream
spot          Spot                        sendir        Send IR
cover         Cover                       script        Script
demo          Demo                        playscript    Play Script
drive         Drive                       showscript    Show Script
lsd           Low Side Drivers            waittime      Wait Time
led           LEDs                        waitdist      Wait Distance
song          Song                        waitangle     Wait Angle
play          Play                        waitevent     Wait Event
sensors       Sensors
cad           Cover and Dock
plsd          PWM Low Side Drivers
```

> Note! Using the script command has special syntax. Look in the examples/scripts directory
> to see exactly how to use the script command. Also, the stream, song and qlist instructions
> take in a variable number of arguments, omit the first argument in these cases (number of
> packets).
> Note #2! The pdf is actually wrong for qlist; the iCreate does take in the number of packets
> for qlist. Again this is implicit in the language so it doesn't affect how to use this program.

# TODO
* [ ] output to file in binary  
* [ ] argument handling on integer bounds for all instructions  
* [ ] Windows support (should make lex/yacc output in a platform independent way)

# NOTICE
This project is licensed with the MIT license. `getopt.[ch]` are under the AT&T Public license;
this code was gotten from <http://note.sonots.com/Comp/CompLang/cpp/getopt.html>
