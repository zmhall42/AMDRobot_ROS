# How to Create a Qt GUI

## Install Steps

1. Go to: `https://ros-qtc-plugin.readthedocs.io/en/latest/_source/How-to-Install-Users.html#qt-installer-procedure` and follow instruction for **Installation Procedure for Ubuntu 18.04**.  Use the Bionic Online Installer.

2. Follow the Qt Install Procedure.

## Setup Qt Creator

1. Run Qt Creator from the applications menu.  

2. Select `Tools->Options`.  Then choose the ROS Menu in the left Column.

3. The Page should look like the following:
    - Default Distribution: **/opt/ros/noetic**
    - Default Build System: **CatkinMake**
    - Default Code Styles: **Qt [built-in]**
    - Default ROS Distros: **/opt/ros**

    Click `Apply`, then `OK`.

## Make a New Project

1. After openeing Qt Creator, select `New Project`.

2. Under `Projects` in the left pane, select `Other Project`.  In the middle pane, select `ROS Workspace`.  This does not create a new workspace, it just uses the catkin_ws.  Then select `Choose...` at the bottom right.

3. Provide the `Name` of the new project.  For a test project, you can use **catkin_ws**.  Make sure the `Distribution` is **/opt/ros/noetic** and the `Build System` is **CatkinMake**.  Choose your `Workspace Path` to be the catkin_ws found in **/home/username/catkin_ws** and click `Open` at the top right.  When you are returned to the pop-up window, select `Next >`.

4. Review your project setup files and select `Finish` to create your project.

## Open an Existing Project

1. After openeing Qt Creator, select `Open Project`.  Navigate to the project inside of the catkin_ws at **/home/username/catkin_ws/** and click `Open` at the top right.

## Thing

After adding files, go to .pro file and after `Config` add a line that says:

```
INCLUDEPATH += /opt/ros/noetic/include
```

This allows it to find the ROS libraries.
