# SingularityBOOT

SingularityBOOT is an iHex bootloader for the Raspberry PI. 

SingularityBOOT currently implements the full iHex specification allowing for a download anywhere in a 4GB address space. It also detects the code entry point, which make room for a bit more freedom for the application to be placed somewhere else other than the typical 0x8000.

SingularityBOOT also uses the RPI UART PL011, because this UART have a dedicated clock that can be read from the GPU mailbox and calculate the configuration parameters during execution time, making it adaptable if future RPI firmware changes the clock rates.

At the moment it supports the following boards:
	
	- RPI3
	- RPI4

For detailed information how to use SingularityBOOT read the README file in the respective board folder.

# Contributions

If you find any bug please report it in the issues tab. 
If you are kind enough to sugest a fix please open a Pull Request.

# Porting

To port SingularityBOOT to a new board, the folder "board_rpi3" should be replicated with the new board details. The key points are the Peripheral addresses and the start.S asm file that handle the initial state of the processor.

Cheers
Tiago

