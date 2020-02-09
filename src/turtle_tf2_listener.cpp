#include "learning_tf2/turtle_tf2_listener.h"

TurtleTf2Listener::TurtleTf2Listener() : tf_listener(tf_buffer)
{
    turtle_vel = nh.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 1);
    spawn_turtle();
}

void TurtleTf2Listener::spawn_turtle()
{
    ros::service::waitForService("spawn");
    ros::ServiceClient spawner = nh.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn turtle;
    turtle.request.x = 4;
    turtle.request.y = 2;
    turtle.request.theta = 0;
    turtle.request.name = "turtle2";
    spawner.call(turtle);
}

void TurtleTf2Listener::process()
{
    ros::Rate loop_rate(10.0);
    while(ros::ok())
    {
        geometry_msgs::TransformStamped transformStamped;
        try
        {
            transformStamped = tf_buffer.lookupTransform("turtle2", "turtle1", ros::Time(0));
        }
        catch (tf2::TransformException &ex)
        {
            ROS_WARN("%s", ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }

        geometry_msgs::Twist vel_msg;
        vel_msg.angular.z = 4.0 * atan2(transformStamped.transform.translation.y, transformStamped.transform.translation.x);
        vel_msg.linear.x = 0.5 * sqrt(pow(transformStamped.transform.translation.x, 2) + pow(transformStamped.transform.translation.y, 2));
        turtle_vel.publish(vel_msg);

        loop_rate.sleep();
    }
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "turtle_tf2_listener");
    TurtleTf2Listener turtle_tf2_listener;
    turtle_tf2_listener.process();
    return 0;
}



