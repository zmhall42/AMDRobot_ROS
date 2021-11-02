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

### **Plug in the dongle** (it may be okay to leave plugged in before the first step, not sure because it was only ever tried with plugging in at this point)

10. sudo rmmod r8188eu.ko

11. git clone https://github.com/aircrack-ng/rtl8188eus

12. ls    **(to make sure it's there)**

13. cd rtl8188eus

14. sudo -i

15. echo "blacklist r8188eu" > "/etc/modprobe.d/realtek.conf"

16. exit

17. sudo reboot now

18. sudo apt update

19. cd rtl8188eus

20. sudo make

21. sudo make install

22. sudo modprobe 8188eu

23. cd ~

24. sudo apt install wireless-tools

25. iwconfig     **(make sure the dongle comes up, should be Nickname: WIFI@REALTEK.  Mine was on wlan1)**

26. sudo apt install net-tools

27. sudo ifconfig wlan1 down

28. sudo apt install aircrack-ng

29. sudo airmon-ng check kill

## **Set in monitor mode**

30. iwconfig **(should see wlan 1 in Auto mode)**

31. sudo iwconfig wlan1 mode monitor    **--robot stuck here**

32. iwconfig **(should see wlan 1 in Monitor mode)**

33. sudo iwconfig wlan1 up **(start the thing)**

34. sudo airplay-ng --test wlan1 **(injection test)**

35. sudo reboot now

## **Set in AP Mode**

36. nmcli d wifi hotspot ifname wlan1 ssid <insert_name_here> password <insert_password_here>

**Successful for base station as AP but not the robot as a monitor.**
After a restart, the only command you need to run in line 36 and everything works on the base station.
