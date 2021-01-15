# Embedded Visible Light Communication
This repository is dedicated for coursework #5 of CUED IIB 4B25: Embedded System for The Internet of Things 

Full Name : A A Ngurah Arymurti Santosa <br />
College   : University College London <br />
CRSid     : aaans2 <br />

In this project a Visible Light Communication between 2 FRDM-KL03z is demonstrated by using the LPUART module. <br />
The layout of the repository is as follows: <br />
"EmbeddedVLC" is the main repository <br />
"EmbeddedVLC/software" contains the source codes <br />
"platform, lib, and tools" provide KSDK driver files and tool chain to build the source code <br />
"Datasheet" provide the relevant documents of components used in this project <br />
"Schematics" provide eagle.sch documents and .png of the transmitter and receiver circuit <br />
"Demonstration" shows a short demonstration of the system transmitting serial data from one board to another <br />
"Debug" contains outputs of the latest build for the source code. (.srec .hex .bin .elf .map) files can be found here <br /> 
There are two source codes <br />
- lpuart_non_blocking_Tx_CW5, the source code include a menu function to choose tranmission of data. The menu can be opened using JlinkRTTClient <br /> 
- lpuart_non_blocking_Rx_CW5. the source code will receive the Tx signal and display it on PuTTY (Set PuTTY to the correct serial line (e.g COM6 or COM8), set baud rate to 9600, set bit count to 8, set stop bit to 1, and set flow control to XON/XOFF) <br />


