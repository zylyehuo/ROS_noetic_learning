#include <ros/ros.h>
#include <std_msgs/String.h>
#include <qq_msgs/Carry.h>

void chao_callback(qq_msgs::Carry msg)
{
    ROS_INFO(msg.grade.c_str());
    ROS_INFO("%d 星", msg.star);
    ROS_INFO(msg.data.c_str());
}

void yao_callback(qq_msgs::Carry msg)
{
    ROS_WARN(msg.grade.c_str());
    ROS_WARN("%d 星", msg.star);
    ROS_WARN(msg.data.c_str());
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    ros::init(argc, argv, "ma_node");
    printf("this is ma_node~\n");

    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("chao_topic", 10, chao_callback);
    ros::Subscriber sub2 = nh.subscribe("yao_topic", 10, yao_callback);

    while (ros::ok())
    {
        ros::spinOnce();
    }
    
    return 0;
}


// void chao_callback(std_msgs::String msg)
// {
//     ROS_INFO(msg.data.c_str());
// }

// void yao_callback(std_msgs::String msg)
// {
//     ROS_WARN(msg.data.c_str());
// }

// int main(int argc, char *argv[])
// {
//     ros::init(argc, argv, "ma_node");

//     ros::NodeHandle nh;
//     ros::Subscriber sub = nh.subscribe("chao_topic", 10, chao_callback);
//     ros::Subscriber sub2 = nh.subscribe("yao_topic", 10, yao_callback);

//     while (ros::ok())
//     {
//         ros::spinOnce();
//     }
    
//     return 0;
// }
