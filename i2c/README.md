
## DataSheet for I2C EEPROM
[EEPROM datasheet](http://ww1.microchip.com/downloads/en/devicedoc/21713m.pdf)

## Testing i2c with i2c tools:
Detect the i2c devices
```sh
ls -al /dev/i2c*
```

Detect the eeprom address
```sh
i2cdetect -y -r 0
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
10: -- -- -- -- UU -- UU -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- UU -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- UU -- -- -- 
50: -- UU -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- UU -- -- -- -- -- -- -- 
70: 70 71 -- -- -- -- -- --   
```
So our device is 70. We can read data from the device using:
```sh
i2cdump -y 0 0x70
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f    0123456789abcdef
00: 09 10 26 68 0f e7 08 30 20 f1 0e c7 00 00 XX 65    ??&h???0 ???..Xe
10: 00 00 00 00 00 00 00 00 XX 00 00 70 16 90 b0 c0    ........X..p????
20: XX c0 XX 9a XX 01 01 06 a4 ce XX 00 00 e6 XX XX    X?X?X?????X..?XX
30: 3a 80 c4 07 XX 00 06 00 00 00 00 01 00 00 XX 10    :???X.?....?..X?
40: 7e 0a XX 01 00 00 7d 00 00 00 10 fb 2f c4 01 00    ~?X?..}...??/??.
50: 00 7d 00 XX XX 10 7e 0a e8 01 00 00 7d 00 00 00    .}.XX?~???..}...
60: 10 fb 2f c4 01 00 00 7d 00 00 80 00 00 00 40 00    ??/??..}..?...@.
70: 00 00 40 00 80 00 40 00 00 00 40 00 00 00 XX 00    ..@.?.@...@...X.
80: 00 00 00 XX 00 00 00 00 00 00 00 00 00 00 XX 00    ...X..........X.
90: 00 00 XX 00 00 00 00 XX 00 00 00 00 00 00 00 00    ..X....X........
a0: 00 00 00 00 00 00 00 00 00 00 00 00 XX 00 00 00    ............X...
b0: 00 00 00 00 00 00 00 00 XX 00 00 00 00 00 00 00    ........X.......
c0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00    ................
d0: 00 00 00 00 00 00 00 00 00 00 08 00 00 0d 00 00    ..........?..?..
e0: f4 f0 00 00 XX 11 00 00 XX 00 00 XX 0f XX 14 00    ??..X?..X..X?X?.
f0: 40 65 00 f0 XX 00 00 1d 00 a8 00 80 00 00 00 00    @e.?X..?.?.?....
```

## Testing i2c with apps:
CodeSink provides a very good application for testing i2c EEPROMs [EEPROG source code](www.codesink.org/download/eeprog-0.7.6.tar.gz).

This source code has been modified into the test application in the folder eeprom_test.
To build the test program use the following commands:
```sh
# setup build environment using Quartus EDS
~/intelFPGA_pro/17.1/embedded/embedded_command_shell.sh 

# To build the default EEPROG from codesink use the following
# command
arm-linux-gnueabihf-gcc -o eeprog eeprog.c 24cXX.c

# To build a simple test that writes one byte to the EEPROM
arm-linux-gnueabihf-gcc -o eeprom_test eeprom_test.c 24cXX.c
```

Copy the program to your board using scp or manually copying it into the SD card.
And run it as follows:

```sh
./eeprom_test
Writing to the EEPROM: h
Reading from the EEPROM: h
```



