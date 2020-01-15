





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