#!/usr/bin/env python3
#coding=utf-8

import rospy
from std_msgs.msg import String

if __name__ == "__main__":
    rospy.init_node("yao_node")
    rospy.logwarn("this is py_yao_node~")

    pub = rospy.Publisher("yao_topic", String, queue_size=10)

    loop_rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        msg = String()
        msg.data = "py_yao_node_publisher..."
        pub.publish(msg)

        loop_rate.sleep()

