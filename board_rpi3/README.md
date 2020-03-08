# How to use SingularityBOOT on the RPI3

To compile the SingularityBOOT software for the Raspberry PI 3 go to the Makefile and select "board_rpi3" on the variable BOARD.

Check the file Makefile.include inside board_rpi3 if the toolchain is correct, and type "make all" to build the software.

A folder "out" should be created in the root dir where the compiler produced files will be placed.

Copy the "kernel8.img" to the SDCard and configure your config.txt with the following lines:

```
arm_64bit=1
kernel_old=1
disable_commandline_tags=1
```

On the PC side you need a terminal capable of sending raw files like GTKTerm.
Configure the communication parameters and when appear the text "Waiting iHex file" go to (in case of GTKterm) File->Send Raw File and select your .hex file to send.

Wait the transfer to finish and press 'g' to jump to your software.

Hope it helps


![](https://i.imgur.com/rduAELY.png)


