#ifndef __TURTLE_TF2_LISTENER_H
#define __TURTLE_TF2_LISTENER_H

#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

class TurtleTf2Listener
{
public:
    TurtleTf2Listener();
    void process();

private:
    void spawn_turtle();

    ros::NodeHandle private_nh;

    ros::NodeHandle nh;
    ros::Publisher turtle_vel;
    tf2_ros::Buffer tf_buffer;
    tf2_ros::TransformListener tf_listener;
};

#endif // __TURTLE_TF2_LISTENER_H
