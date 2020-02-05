## Setting up build softwares
Install Quartus Pro 17.1 using:
```sh
./QuartusProSetup-17.1.0.240-linux.run
```
Install SoC Embedded Design Suite:
```sh
./SoCEDSProSetup-17.1.0.240-linux.run
```
Test DS-5 installation:
```sh
~/intelFPGA_pro/17.1/embedded/embedded_command_shell.sh
```
if you get DS-5 path not found error edit ```~/intelFPGA_pro/17.1/embedded/env.sh``` and set the path of 
DS-5 manually to your installation directory which was this ```_DS5_ROOT="/usr/local/DS-5_v5.27.1/"``` 
in my case.

## Compiling Hardware Design, Uboot, Linux Device Tree and Linux
1. Hardware Design Compilation [this](https://rocketboards.org/foswiki/Documentation/A10GSRDCompilingHardwareDesign171)
   If you get errors while compiling for time_limited IPs. Remove them from the project
2. [Uboot Compilation](https://rocketboards.org/foswiki/Documentation/A10GSRDGeneratingUBootAndUBootDeviceTree)
3. [Linux Device Tree](https://rocketboards.org/foswiki/Documentation/A10GSRDGeneratingTheLinuxDeviceTreeLTS)
   To enable spidev add the following in ```ghrd_10as066n2.dts``` and then compile the dtb file

```
      spi0: spidev@0 {
        compatible = "spidev";
        reg = <0x0>;
        spi-max-frequency = <1000000>;
        enable-dma = <0x1>;
      };
```
to make it similar to this
```
.....
		a10_hps_i_spim_1_spim: spi@0xffda5000 {
			compatible = "snps,dw-spi-mmio-17.1", "snps,dw-spi-mmio", "snps,dw-apb-ssi";
			reg = <0xffda5000 0x00000100>;
			interrupt-parent = <&a10_hps_arm_gic_0>;
			interrupts = <0x00000000 0x00000066 0x00000004>;	/* appended from boardinfo */
			clocks = <&spi_m_clk>;
			#address-cells = <1>;	/* embeddedsw.dts.params.#address-cells type NUMBER */
			#size-cells = <0>;	/* embeddedsw.dts.params.#size-cells type NUMBER */
			bus-num = <0>;	/* embeddedsw.dts.params.bus-num type NUMBER */
			num-chipselect = <4>;	/* embeddedsw.dts.params.num-chipselect type NUMBER */
			status = "okay";	/* embeddedsw.dts.params.status type STRING */
			tx-dma-channel = <&a10_hps_i_dma_DMASECURE 0x00000010>;	/* appended from boardinfo */
			rx-dma-channel = <&a10_hps_i_dma_DMASECURE 0x00000011>;	/* appended from boardinfo */
			32bit_access;	/* appended from boardinfo */

			spi0: spidev@0 {
        		compatible = "spidev";
        		reg = <0x0>;
        		spi-max-frequency = <20000000>;
        		enable-dma = <0x1>;


				gpio4: gpio-controller {
					compatible = "altr,a10sycon-gpio";	/* appended from boardinfo */
					gpio-controller;	/* appended from boardinfo */
					#gpio-cells = <2>;	/* appended from boardinfo */
					ngpios = <16>;	/* appended from boardinfo */
				}; //end gpio-controller (gpio4)
      		};
		}; //end spi@0xffda5000 (a10_hps_i_spim_1_spim)

....

```
4. [Build Linux](https://rocketboards.org/foswiki/Documentation/GSRDCompilingLinux)

## Setting up environment in CentOS:
Setting up ethernet:
```sh
    ifconfig eth0 192.168.101.205 netmask 255.255.255.0
    route add default gw 192.168.101.1
    echo "nameserver 192.168.101.1" > /etc/resolv.conf
    ping google.com
```

## Setup for CentOS:
Get parted
```sh
	yum install parted
	yum install dosfstools
	yum install nano
	yum install xz
```
Get argparse for Python2.6
```sh
	wget http://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm
	sudo rpm -i epel-release-6-8.noarch.rpm
	rm epel-release-6-8.noarch.rpm
	sudo yum install python-argparse
```

## Image Creation:
Assemble the following files in a folder:

| Item                               | Description                                                              |
|------------------------------------|--------------------------------------------------------------------------|
| extlinux/extlinux.conf             | U-Boot and U-Boot Device Tree Image                                      |
| u-boot.img                         |                                                                          |
| fit_spl_fpga.itb                   |                                                                          |
| spl_w_dtb-mkpimage.bin             |                                                                          |
| ghrd_10as066n2.core.rbf            | Compressed FPGA configuration file                                       |
| ghrd_10as066n2.periph.rbf          | Compressed FPGA IO configuration file                                    |
| socfpga_arria10_socdk_sdmmc.dtb    | Linux Device Tree Blob                                                   |
| zImage                             | Compressed Linux kernel image                                            |
| gsrd-console-image-arria10.tar.xz  | Root filesystem as compressed tarball (built together with kernel image) |

Here zImage and gsrd-console-image-arria10 can be symbolic links, so copy both the link and the file it points to. 

```sh
mkdir ref_sd_image
cd ref_sd_image
# copy the above files in ref_sd_image
# extract the linux rootfs
sudo tar xf Angstrom-gsrd-console-image-glibc-ipk-v2019.06-arria10.rootfs.tar.xz 
```

Create the SD card image:
```sh
sudo make_sdimage.py  \
  -f \
  -P uboot_w_dtb-mkpimage.bin,num=3,format=raw,size=10M,type=A2  \
  -P rootfs/*,num=2,format=ext3,size=1500M  \
  -P zImage,ghrd_10as066n2.core.rbf,ghrd_10as066n2.periph.rbf,socfpga_arria10_socdk_sdmmc.dtb,num=1,format=vfat,size=500M  \
  -s 2G  \
  -n sdimage.img
```

## Burn Image on SD Card:
Use balena etcher to burn the sdimage.img to the SD card

## Building applications for SoC:
```sh
~/intelFPGA_pro/17.1/embedded/embedded_command_shell.sh
arm-linux-gnueabihf-gcc -o hello hello.c
```
