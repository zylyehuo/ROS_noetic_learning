#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "yao_node");
    printf("this is yao_node~\n");

    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<std_msgs::String>("yao_topic", 10);

    ros::Rate loop_rate(10);

    while (ros::ok())
    {
        std_msgs::String msg;
        msg.data = "yao_node_publisher...";
        pub.publish(msg);
        loop_rate.sleep();
    }
    
    return 0;
}
