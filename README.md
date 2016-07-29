Emu430 - An MSP430 Emulator
==========

A very, very early stage emulator for the MSP430 line of microcontrollers.  

The end goal is have an emulator program that can take in hex files, run
the code for the mcu, and continuously take in input to the input memory addresses
and to output on the output memory addresses.  

Currently, the project is in its very earliest stages - currently, instructions
are translated, but only the add instruction is implemented.  


The current plan for development is as follows:  
 1. Translate all 27 instructions into functions  
 2. Provide an easy interface for writing to the IN memory locations and reading from the OUT memory locations  
 3. Add the ability to read in Intel HEX files  
 4. Add interrupt support  
