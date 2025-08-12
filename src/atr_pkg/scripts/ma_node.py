#!/usr/bin/env python3
#coding=utf-8

import rospy
from std_msgs.msg import String
from qq_msgs.msg import Carry

def chao_callback(msg):
    rospy.loginfo(msg.grade)
    rospy.loginfo(str(msg.star)+"星")
    rospy.loginfo(msg.data)

def yao_callback(msg):
    rospy.logwarn(msg.grade)
    rospy.logwarn(str(msg.star)+"星")
    rospy.logwarn(msg.data)


if __name__ == "__main__":
    rospy.init_node("ma_node")
    rospy.logwarn("this is py_ma_node~")

    sub = rospy.Subscriber("chao_topic", Carry, queue_size=10, callback=chao_callback)
    sub2 = rospy.Subscriber("yao_topic", Carry, queue_size=10, callback=yao_callback)

    while not rospy.is_shutdown():
        rospy.spin()

# def chao_callback(msg):
#     rospy.loginfo(msg.data)

# def yao_callback(msg):
#     rospy.logwarn(msg.data)


# if __name__ == "__main__":
#     rospy.init_node("ma_node")
#     rospy.logwarn("this is py_ma_node~")

#     sub = rospy.Subscriber("chao_topic", String, queue_size=10, callback=chao_callback)
#     sub2 = rospy.Subscriber("yao_topic", String, queue_size=10, callback=yao_callback)

#     while not rospy.is_shutdown():
#         rospy.spin()
