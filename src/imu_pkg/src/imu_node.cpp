#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <tf/tf.h>

ros::Publisher imu_pub;

void IMUCallback(sensor_msgs::Imu imu_msg)
{
    if(imu_msg.orientation_covariance[0] < 0)
    {
        return;
    }
    else
    {
        tf::Quaternion quaternion(
            imu_msg.orientation.x,
            imu_msg.orientation.y,
            imu_msg.orientation.z,
            imu_msg.orientation.w
        );

        double roll, pitch, yaw;

        tf::Matrix3x3(quaternion).getRPY(roll, pitch, yaw);

        roll = roll * 180 / M_PI;
        pitch = pitch * 180 / M_PI;
        yaw = yaw * 180 / M_PI;

        ROS_INFO("滚转=%.0f, 俯仰=%.0f, 偏航=%.0f", roll, pitch, yaw);

        double target_yaw = 90;
        double diff_angle = target_yaw - yaw;

        geometry_msgs::Twist imu_vel_cmd_msg;
        imu_vel_cmd_msg.angular.z = diff_angle * 0.01;  // rad/s
        imu_vel_cmd_msg.linear.x = 0.1;  // m/s
        imu_pub.publish(imu_vel_cmd_msg);

    }
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    ros::init(argc, argv, "imu_node");
    ros::NodeHandle nh;

    ros::Subscriber imu_sub = nh.subscribe("/imu/data", 10, &IMUCallback);
    imu_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::spin();

    return 0;
}
