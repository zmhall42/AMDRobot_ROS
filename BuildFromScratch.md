# Build From Scratch
Last Updated: 2021-10-06

Latest addition: Added this repository to the Pi and built locally.

If we lose the project for any reason, this file contains the exact steps to follow to get back to the most recent state of the project.  Follow all steps in order unless stated otherwise.  All steps work for both the Robot and the Base Station unless otherwise noted.

## Step 1: Format the SD Card
- Remove the micro SD card from the Pi.  Put the micro SD Card into an SD card adapter and plug into your computer.
- Download the Raspberry Pi Imager Tool found here: https://www.raspberrypi.com/software/.  Download the one that best suits your computer's operating system (OS).
- Once downloaded, run the installer.  This will install the Imager and then open it after installing.  If it is already installed, you can just run the Imager.  Running the already installed imager will bring up an install page, which is odd, but correct.  Follow on screen prompts to set it up.  When it opens to the "Choose OS", "Choose SD Card", and "Write" screen, wait here.
- Download the Raspberry Pi image found here: https://docs.emlid.com/navio2/configuring-raspberry-pi.  It is called the Emlid Raspberry Pi OS Buster [XZ, 662 MB].
- You will use the Raspberry Pi Imager 2 times.  The first time, click `CHOOSE OS` and select one of the last options `erase`.  This erases the SD Card to start from scratch.
- Click `CHOOSE SD CARD` and pick the SD Card option that matched the drive letter of the micro SD Card you have inserted into your computer.
- Now you can click `WRITE` to write this image to your SD card.  This will take a minute to do, so go grab a coffee or a beer. Or don't, you maniac.
- When completed, it will say to remove the SD Card from the computer.  Remove the SD Card and reinsert it.  
- Going back to the Raspberry Pi Imager Tool, click `CHOOSE OS` and select the last option `Use custom`.  You will then find on your computer where you downloaded the previous step's Raspberry Pi image and select it.
- Click `CHOOSE SD CARD` and pick the SD Card option that matched the drive letter of the micro SD Card you have inserted into your computer.
- Now you can click `WRITE` to write this image to your SD card.  This will take a slightly longer minute.
- When completed, it will say to remove the SD Card from the computer.  Remove the SD Card and close the Imager.
- Reinsert the SD Card.  Open the /boot directory on the SD card and creat a new text document titled `wpa_supplicant.conf`.  Be sure to change the extension from `.txt` to `.conf`.  The computer will say it may cause errors, but that is fine.  Open the file and add the following:
```
network={
  ssid="EagleNet"
  psk="yourpsk"
}
```
Replace `yourpsk` with your Wi-Fi password to EagleNet.  Leave the quotes there for both lines.  Save and exit.
- Create a file called `ssh` with no extension.  The computer may say again that it will cause problems, just click okay and keep going.  Thsi file tells the Pi on startup to enable the ssh.
- Insert the SD Card into the Raspberry Pi and power it on.  The Pi will boot in the terminal.
- Plug in a keyboard so you can type commands on the Pi.
- The Raspberry Pi will ask for the user and password.  The default user is `pi` and the default password is `raspberry`.
- To verify you are connected, type the following:
```
hostname -I
```
It should return an IP address that looks similar to this 10.104.1.196.  If it does not return an IP, your ssid or password are wrong.  This step gives us the IP address that we will use in Step 2 to remote into the Pi.

## Step 2: Remote into the Pi.
- Typing on a tiny keyboard and reading from a small screen can be hard.  Let's fix that.  Download and install PuTTy on your computer, if it is not already installed.  Go here https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html to download the latest version for your computer.  If you have a windows machine, you will want the latest download in the `Package Files` section under the `MSI header`.  Most people will get the 64-bit x86 version.  It will look something like this `putty-64bit-0.76-installer.msi`.
- Follow the installer and put it some place you can find it easily.  You will be using it a lot. A. LOT.
- Now we can log in using PuTTY.  Remember the IP you got at the end of Step 1? No? You should've written it down.  If not, use `hostname -I` to get it again.  Open PuTTY and make sure `Session` is selected in the top left under `Category`.  In the `Host Name` blank, type the IP of the Raspberry Pi.  Make sure the `SSH` bubble is selected below the IP and the `Port` is set to 22.  Save this setup as a profile for easier loading by entering a name in the `Saved Session` blank and clicking `Save`.  When you reboot the Pi from PuTTY, you lose connection with it and you have to do this step everytime you want to open it.  It saves time to create an easy to remember profile name so you can start PuTTY, select the profile name, and hit load.  Now select `Open` at the bottom right to SSH into the Pi's terminal.
- Log in again.  Now you can run commands from you computer to control the Pi.

## Step 3: Configure the Pi's settings.
- In the terminal (Pi or PuTTy), type the following to begin setting up the Pi for your area:
```
sudo raspi-config
```
- Since I stated above how to navigate this menu, I'll skip the baby talk and get to the nitty-gritty.  Rapid fire, let's go.  Go to `1 System Options`, `S4 Hostname`, `Enter`.  The Robot should be named `AMDRobot-Robot` and the Base station should be named `AMDRobot-Base`.  Then hit `Enter`.
- Now go to `5 Localization Options`, `L2 Timezone`, select `America`, then `Chicago` for CST.
- Now go to `5 Localization Options`, `L3 Keyboard Layout`, select `OK` on the selected keyboard, then `Other`, scroll to locate `US`, select `OK`, then scroll to the op and highlight `English US` then press OK to set the keyboad as a standard English keyboard.
- Now go to `5 Localization Options`, `L4 WLAN Country`, select `US`, then `Enter` to confirm.
- Now go to `6 Update` to update the changes and update the tool to the lastest version.  Once this completes, you're donw with the configuration tool.  Select `FINISH` to escape.
- Reboot the Pi to make the changes.  PuTTy will lose connection, but that's okay.  That's why we created a profile to remote in faster.  You did do that, didn't you?

## Step 4: Set up the catkin workspace for creating and running custom ROS code.
- Make sure the `.catkin` workspace found at `/opt/ros/noetic/` has been created.
```
cd /opt/ros/noetic && ls -a
```
- If you see a file in white called `.catkin`, it exists.  If it does not exist, something is wrong with the image file.  The SD Card may need to be re-imaged, but this problem has yet to occur.
- Source the catkin environment.
```
source /opt/ros/noetic/setup.bash
```
- Create and build the catkin workspace.
```
mkdir -p ~/catkin_ws/src 
```
```
cd ~/catkin_ws/ 
```
```
catkin_make
```
- Source the workspace to the environment.
```
source devel/setup.bash
```
- Verify previous step occurred by typing the following.
```
echo $ROS_PACKAGE_PATH 
```
It should return `/home/pi/catkin_ws/src:/opt/ros/noetic/share `.
- Permenantly add the catkin workspace to the ROS environment by sourcing the generated setup file.
```
cd ~
```
```
nano .bashrc
```
Type at the bottom of the `.bashrc` file these two lines:
```
source /opt/ros/noetic/setup.bash
source /home/pi/catkin_ws/devel/setup.bash
```
To exit, hit `CTRL` + `X`, `Y`, then hit `enter`.

## Step 5: Download all required repos.
- For this project, we are using: this repo; the Navio2 examples repo; and the teleop_twist_keyboard repo.
- Go to the destination folder.
```
cd ~/catkin_ws/src
```
- Clone this repo to destination.
```
git clone https://github.com/zmhall42/AMDRobot_ROS.git
```
- Clone Navio2 repo to destination.
```
git clone https://github.com/emlid/Navio2.git
```
- Clone teleop-twist-keyboard repo to destination.
```
git clone https://github.com/ros-teleop/teleop_twist_keyboard.git
```

## Step 6: Make the downloaded repos.
- Build the packages in the catkin workspace.
```
cd ~/catkin_ws 
```
```
catkin_make
```

You are now caught back up.  Simple, right?
