# Introduction:

This markdown file (.md) is a step by step tutorial for creating a disk image of a drive.



# **README**

**NOTE: Only use** `sudo` **(administratro privlages) when instructed. Using** `sudo` **could corrupt the the system if not careful.**

**NOTE:** `dd` **is a powerful tool.  Be careful using because data could accidentally be erased.**

**NOTE: The following links should be read throughly before continuing:**

https://wiki.archlinux.org/title/Dd

https://wiki.archlinux.org/title/file_systems

https://www.gnu.org/software/coreutils/manual/html_node/dd-invocation.html#dd-invocation

**The above links may be from the Archlinux Wiki page, but Archlinux has very good documentation and some of it can be carried over to other distributions of Linux.**



# Creating a Disk Image:

1.) The first step is to make directory to mount the drive to:

    sudo mkdir /mnt/external


2.) Insert the flash drive if it is not inserted already.  To generate a list of all the drives connected run:

    sudo fdisk -l

Find the drive to be mounted.


3.) Once the drive is identified, mount the drive by executing the follwing:

    sudo mount /dev/sda1 /mnt/external

Note that `sda` is the device, insert the name of the device from the list generated in step 2.


4.) Once the external drive is mounted, determine how much data on the drive needs to be backed up.  The following will generate a table of used and unused space (Generate memory in Powers of 1024):

    sudo df -h

Note that the size given will most likely be in Gibibytes or Mebibytes.  Also round up to the next whole number to make sure all data is copied.


5.) Calculate the numebr of blocks needed to capture the data.  Determine an appropiate block size to use for `dd`.


6.) Now that the device is mounted and all the information is acquired, it is time to create a disk image of the drive:

    sudo dd if=/dev/sda bs=1MiB count=<n> iflag=fullblock status=progress | sudo xz -z | sudo split -a 1 -b 3.8GB - /mnt/external/backup.img.xz

In the command above, `sda` is the name of the drive to create an image of.  This can also be found from the command in step 2.

`bs` is the block size.

`count` is the number of blocks.

`iflag=fullblock` will ensure `count` corresponds to the number of full input blocks.

`status=progress` will show the status of the execution.

`xz` will put the file in a `.xz` file.


The command above will take sometime to execute, so be patient.


5.) Get the disk info

    sudo fdisk -l /dev/sda > /path/to/list_fdisk.info


6.) Unmount the drive

    umount /mnt/external



# Restoring the Sytem from the Disk Image:

1.) To restore the system:

    sudo cat /path/to/backup.img.xz* | sudo xzcat | sudo dd of=/dev/sda status=progress bs=1MiB

Where `sda` is the name of the disk to be restored.  This can be determined using:

    sudo fdisk -l


