# AMDRobot_ROS
Collection of nodes created by the 2021 Autonomous Metal Detector Robot senior design group at Tennessee Technological University.  This is a joint project consisting of both a Mechanical and an Electrical Engineering group.  The robot is a tank-drive layout with a metal detector attached to it.  The remote base station is communicating with the robot over Wi-Fi using Ad Hoc mode.

## System Setup
Note: This is written specifically for this project.  Following these instructions may not produce the same results for other creators.

This repository is set up like a ROS package, where the base directory of the repository is the root of the package.  This package was built specifically for ROS Noetic; no other distributions of ROS have been tested.  Both the robot and base station are controlled by a Raspberry Pi 4 model B 4Gb and a Navio2 board.  Since the Navio2 specifically requires ROS Noetic, we used the Raspberry Pi image found on the Emlid Docs website found here: https://docs.emlid.com/navio2/configuring-raspberry-pi.  See [BuildFromScratch.md](BuildFromScratch.md) for details.

## Using this Repo.
### Updating the local version from the cloud.
- Go to root of the repo on the local machine.
```
cd ~/catkin_ws/src/AMDRobot_ROS/
```
- Fetch and merge changes from Github.
```
git pull
```
### Add newly created local files to Github repo.
### Push changes to Github repo.

## Future Expansion
