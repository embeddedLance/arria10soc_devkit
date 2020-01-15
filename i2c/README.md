
## DataSheet for I2C EEPROM
[EEPROM datasheet](http://ww1.microchip.com/downloads/en/devicedoc/21713m.pdf)

[EEPROG source code](www.codesink.org/download/eeprog-0.7.6.tar.gz)

## Testing i2c with i2c tools:
Detect the i2c devices
```sh
ls -al /dev/i2c*
```

Detect the eeprom address
```sh
i2cdetect -y -r 0
```
A line would contain text similar to this:
```
50: -- UU -- -- -- -- -- --
60: -- -- -- -- -- -- -- --
70: 70 71 -- -- -- -- -- --
```
Our device is 70.

Read data from the device using:
```sh
i2cdump -y 0 0x70
```

## Testing i2c with apps:
```sh
# setup build environment using Quartus EDS
~/intelFPGA_pro/17.1/embedded/embedded_command_shell.sh 

# To build the default EEPROG from codesink use the following
# command
arm-linux-gnueabihf-gcc -o eeprog eeprog.c 24cXX.c

# To build a simple test that writes one byte to the EEPROM
arm-linux-gnueabihf-gcc -o eeprom_test eeprom_test.c 24cXX.c
```




