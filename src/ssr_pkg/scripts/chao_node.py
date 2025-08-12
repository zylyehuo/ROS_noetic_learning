#!/usr/bin/env python3
#coding=utf-8

import rospy
from std_msgs.msg import String
from qq_msgs.msg import Carry

if __name__ == "__main__":
    rospy.init_node("chao_node")
    rospy.loginfo("this is py_chao_node~")

    pub = rospy.Publisher("chao_topic", Carry, queue_size=10)

    loop_rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        msg = Carry()
        msg.grade = "王者"
        msg.star = 50
        msg.data = "py_chao_node_publisher..."
        pub.publish(msg)

        loop_rate.sleep()

# if __name__ == "__main__":
#     rospy.init_node("chao_node")
#     rospy.loginfo("this is py_chao_node~")

#     pub = rospy.Publisher("chao_topic", String, queue_size=10)

#     loop_rate = rospy.Rate(10)

#     while not rospy.is_shutdown():
#         msg = String()
#         msg.data = "py_chao_node_publisher..."
#         pub.publish(msg)

#         loop_rate.sleep()

