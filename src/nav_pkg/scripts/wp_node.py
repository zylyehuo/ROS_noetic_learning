#!/usr/bin/env python3
# coding=utf-8

import rospy
from std_msgs.msg import String


def NavResultCallback(msg):
    rospy.loginfo("导航结果 = %s",msg.data)

if __name__ == "__main__":

    rospy.init_node("py_wp_node")
    navi_pub = rospy.Publisher("/waterplus/navi_waypoint", String, queue_size=10)

    result_sub = rospy.Subscriber("/waterplus/navi_result", String, NavResultCallback,queue_size=10)

    rospy.sleep(1)

    msg = String()
    msg.data = '3'

    navi_pub.publish(msg)

    rospy.spin()
