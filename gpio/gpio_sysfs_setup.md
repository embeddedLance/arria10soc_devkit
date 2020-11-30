The sysfs interface is a real blessing in embedded linux. 

Check available addresses in the gpio driver:
```sh
ls ./sys/devices/platform/sopc@0/'
```
The result will contain these: ```0xffc02900, 0xffc02a00 and 0xffc02b00```. 

From the **GPIO Address Map** in a10_5v4.pdf(pg 4296):

| Module Instance | Base Address | 
| =============== | ============ |
| i_gpio_0_gpio   | 0xFFC02900   | 
| i_gpio_1_gpio   | 0xFFC02A00   | 
| i_gpio_2_gpio   | 0xFFC02B00   |






## Driving an IO pin:
After you have calculated the virtual address for the io pin you need to 
run the following steps

```sh
# export the virtual address
root@arria10:/# echo "1938" > /sys/class/gpio/export;

# set the direction of the gpio
root@arria10:/#  echo "out" > /sys/class/gpio/gpio1938/direction;

# drive a value to it
root@arria10:/# echo "1" > /sys/class/gpio/gpio1937/value

```
