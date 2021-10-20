#!/usr/bin/env python
# license removed for brevity
import rospy
import serial
from std_msgs.msg import String
   
def sensors():
	pub = rospy.Publisher('obstacle_avoidance', String, queue_size=10)
        rospy.init_node('sensors', anonymous=True)
        rate = rospy.Rate(10) # 10hz
        while not rospy.is_shutdown():
        	if ser.in_waiting > 0:
           		line = ser.readline().decode('utf-8').rstrip()
			rospy.loginfo(line)
           		pub.publish(line)
           	rate.sleep()
   
if __name__ == '__main__':
	try:
           	ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
           	ser.flush() 
           	sensors()
	except rospy.ROSInterruptException:
           	pass
