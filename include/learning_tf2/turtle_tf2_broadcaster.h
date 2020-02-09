#ifndef __TURTLE_TF2_BROADCASTER_H
#define __TURTLE_TF2_BROADCASTER_H

#include <ros/ros.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <turtlesim/Pose.h>

class TurtleTf2Broadcaster
{
public:
    TurtleTf2Broadcaster(int argc, char** argv);
    void process();

private:
    void pose_callback(const turtlesim::PoseConstPtr& msg);

    ros::NodeHandle private_nh;

    ros::NodeHandle nh;
    ros::Subscriber sub;
    tf2_ros::TransformBroadcaster br;
    std::string turtle_name;
};

#endif // __TURTLE_TF2_BROADCASTER_H
