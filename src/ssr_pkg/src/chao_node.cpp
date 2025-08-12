#include <ros/ros.h>
#include <std_msgs/String.h>
#include <qq_msgs/Carry.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "chao_node");
    printf("this is chao_node~\n");

    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<qq_msgs::Carry>("chao_topic", 10);

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        qq_msgs::Carry msg;
        msg.grade = "王者";
        msg.star = 50;
        msg.data = "chao_node_publisher...";
        pub.publish(msg);
        loop_rate.sleep();
    }
    
    return 0;
}

// int main(int argc, char *argv[])
// {
//     ros::init(argc, argv, "chao_node");
//     printf("this is chao_node~\n");

//     ros::NodeHandle nh;
//     ros::Publisher pub = nh.advertise<std_msgs::String>("chao_topic", 10);

//     ros::Rate loop_rate(10);

//     while (ros::ok())
//     {
//         std_msgs::String msg;
//         msg.data = "chao_node_publisher...";
//         pub.publish(msg);
//         loop_rate.sleep();
//     }
    
//     return 0;
// }
