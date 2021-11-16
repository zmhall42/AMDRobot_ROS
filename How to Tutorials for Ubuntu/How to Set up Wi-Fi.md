# **How to Set up Wi-Fi from Scratch**

## **Instructions:**

### **With the dongle unplugged**

1. sudo apt update

2. sudo apt upgrade

3. sudo apt autoremove

4. sudo reboot now

5. sudo apt install bc

6. sudo apt install build-essential

7. sudo apt-get install libelf-dev

8. sudo apt-get install linux-headers-\`uname -r\`

9. sudo apt install dkms

### **Plug in the dongle, NEVER EVER REMOVE NOW** (it may be okay to leave plugged in before the first step, not sure because it was only ever tried with plugging in at this point)

1. sudo rmmod r8188eu.ko

2. git clone https://github.com/aircrack-ng/rtl8188eus

3. ls    **(to make sure it's there)**

4. cd rtl8188eus

5. sudo -i

6. echo "blacklist r8188eu" > "/etc/modprobe.d/realtek.conf"

7. exit

8. sudo reboot now

9. sudo apt update

10. cd rtl8188eus

11. sudo make

12. sudo make install

13. sudo modprobe 8188eu

14. cd ~

15. sudo apt install wireless-tools

16. iwconfig     **(make sure the dongle comes up, should be Nickname: WIFI@REALTEK.  Mine was on wlan1)**

17. sudo apt install net-tools

18. sudo ifconfig wlan1 down

19. sudo apt install aircrack-ng

20. sudo airmon-ng check kill

### **Set Robot in monitor mode**

1. iwconfig **(should see wlan0 in Auto mode for the dongle)**

2. sudo iwconfig wlan0 mode monitor

3. iwconfig **(should see wlan 1 in Monitor mode)**

4. sudo iwconfig wlan0 up **(start the thing)**

5. sudo airplay-ng --test wlan0 **(injection test)**

6. sudo reboot now

### **Set Base Station in AP Mode**

(also do the above for the robot monitor mode, then do this)

1. sudo nano /etc/netplan/50-cloud-init.yaml

2. Change where you have `wlan0` set for EagleNet to `wlan1`

3. sudo reboot now

4. nmcli d wifi hotspot ifname wlan0 ssid AMDBase password raspberry

## **Configure Wi-Fi networks on Robot**

1. sudo nano /etc/netplan/50-cloud-init.yaml

2. Add the following at the end (the wifis is in same column as `version: 2` and each indentation is 4 spaces, not tab.):

```
wifis: 
    wlan1:
        dhcp4: true
        optional: true
        access-points:
            "EagleNet":
                password: "E8fdADXR"
    wlan0:
        dhcp4: no
        addresses: [10.42.0.2/24]
        gateway4: 10.42.0.1
        nameservers:
            addresses: [8.8.8.8,8.8.4.4]
        access-points:
            "AMDBase":
                password: "raspberry"
```

`Ctrl` + `x`, `y`, `Enter` to exit.

3. sudo reboot now

## **Set up AP to start automatically on reboot**

1. sudo crontab -e

2. Add at bottom: 

```
@reboot nmcli d wifi hotspot ifname wlan0 ssid AMDBase password raspberry
```

`Ctrl` + `x`, `y`, `Enter` to exit.

4. sudo reboot now
