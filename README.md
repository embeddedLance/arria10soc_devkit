This repository follows the documentation given by Rocket boards to compile and run linux and userspace application on A10 GSRD v17.1. This [link](https://rocketboards.org/foswiki/Documentation/A10GSRDV171UserManual) has been followed.

Installing USB-Blaster II in Ubuntu/Linux:
Use the procedure on pg10 for Intel FPGA Download Cable II:
https://www.intel.com/content/dam/www/programmable/us/en/pdfs/literature/ug/ug_usb_blstr.pdf
```
BUS=="usb", SYSFS{idVendor}=="09fb", SYSFS{idProduct}=="6010", MODE="0666"
BUS=="usb", SYSFS{idVendor}=="09fb", SYSFS{idProduct}=="6810", MODE="0666"
```
Setting up ethernet in Uboot:
```
U-Boot> setenv ipaddr 192.168.1.126
U-Boot> setenv serverip 192.168.1.1
U-Boot> setenv netmask 255.255.255.0
U-Boot> saveenv```
```
Checking the ethernet driver in Uboot
```
 mdio list

FSL_MDIO0:
0 - RealTek RTL8211E <--> FM1@DTSEC2
1 - RealTek RTL8211E <--> FM1@DTSEC4
2 - RealTek RTL8211E <--> FM1@DTSEC5
3 - RealTek RTL8211DN <--> FM1@DTSEC3


=> mii read 0-1 0-6
addr=00 reg=00 data=1140
addr=00 reg=01 data=7969
addr=00 reg=02 data=001C
addr=00 reg=03 data=C915
addr=00 reg=04 data=01E1
addr=00 reg=05 data=C1E1
addr=00 reg=06 data=000D
```
