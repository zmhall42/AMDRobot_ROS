# AMDRobot_ROS

Collection of nodes created by the 2021 Autonomous Metal Detector Robot senior design group at Tennessee Technological University.  This is a joint project consisting of both a Mechanical and an Electrical Engineering group.  The robot is a tank-drive layout with a metal detector attached to it.  The remote base station is communicating with the robot over Wi-Fi using Ad Hoc mode.

## **DO NOT USE Tank_Drive_02 ON THE UNO, IT LETS THE MAGIC SMOKE OUT. Redo the PID Setup and tuning and params.**

# System Setup

Note: This is written specifically for this project.  Following these instructions may not produce the same results for other creators.

This repository is set up like a ROS package, where the base directory of the repository is the root of the package.  This package was built specifically for ROS Noetic; no other distributions of ROS have been tested.  Both the robot and base station are controlled by a Raspberry Pi 4 model B 4Gb and a Navio2 board.  Since the Navio2 specifically requires ROS Noetic, we used the Raspberry Pi image found on the Emlid Docs website found here: https://docs.emlid.com/navio2/configuring-raspberry-pi.  See [BuildFromScratch.md](BuildFromScratch.md) for details.

# Users and Passwords

**Robot and Base Station:**

- Username: AMDRobot
- Password: ttu_AMD1

# Using this Repo

## Updating the local version from the cloud

- Go to root of the repo on the local machine.

```
cd ~/catkin_ws/src/AMDRobot_ROS/
```

- Fetch and merge changes from Github.

```
git pull
```

## Add newly created local files to Github repo

## Push changes to Github repo

# Communicate over the same network via WI-Fi or LAN(Ethernet) if both Pi's are connected to EagleNet

- Remote into both Pi's from your laptop using 2 instances of PuTTy.
- Get IP's of both Pi's.

```
hostname -I
```

Type in each terminal.  If plugged into ethernet too, the first IP is the ethernet connection IP and the second is the WI-FI IP.  If only connected via 1 method, it will return the IP of that method.  Use the IP of the method you wish to use.

- In the Base Station, type the following at the botom of the bashrc file in `~/.bashrc`:

```
export ROS_MASTER_URI=http://Base_Station_IP:11311
```

```
export ROS_HOSTNAME=Base_Station_IP
```

```
export ROS_IP=Base_Station_IP
```

Save and Exit using `Ctrl` + `x`, `y`, then `Enter`.

- In the Robot, type the following at the botom of the bashrc file in `~/.bashrc`:

```
export ROS_MASTER_URI=http://Base_Station_IP:11311
```

Yes, this should be the only field the same on both the Base Station and the Robot.

```
export ROS_HOSTNAME=Robot_IP
```

```
export ROS_IP=Robot_IP
```

Save and Exit using `trl` + `x`, `y`, then `Enter`.

- Before running the core, you must secure shell (SSH) into each machine from the other machine to make sure they can recognize each other when ROS runs.  Type the following on the robot:

```
ssh AMDRobot@Base_Station_IP
```

Type yes to accept the security key and enter the password.  Once you have successfully ssh's in, you can type `exit` to go back to the robot's terminal.  On the Base station, type:

```
ssh ubuntu@Robot_IP
```

Type yes to accept the security key and enter the password.  Once you have successfully ssh's in, you can type `exit` to go back to the base station's terminal.  Note that the IP's must be entered as XXX.XXX.XXX.XXX, not "Robot_IP" or "Base_Station_IP".

- In the base station, use tmux on the Base Station and create 2 windows.

```
tmux new
```

Use `CTRL` + `B` the `"` to split it vertically.

- In the first window, run:

```
roscore
```

- Change to the second window using `Ctrl` + `B` then `O` and run:

```
rosrun AMDRobot_ROS listener
```

- In the Robot, run:

```
rosrun AMDRobot_ROS talker
```

- TA-DA!!!!!!
- To end either program, use `Ctrl` + `C`. To exit the tmux windows on the Base Station, do `Ctrl` + `B` and `X` then `Y` for both panes.

# Future Expansion
