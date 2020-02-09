#include "learning_tf2/turtle_tf2_broadcaster.h"

TurtleTf2Broadcaster::TurtleTf2Broadcaster() : private_nh("~")
{
    private_nh.param("turtle_name", turtle_name, {"/turtle1"});
    sub = nh.subscribe(turtle_name+"/pose", 1, &TurtleTf2Broadcaster::pose_callback, this);
    
    std::cout << "=== turtle_tf2_broadcaster ===" << std::endl;
    std::cout << "turtle_name: " << turtle_name << std::endl;
}

void TurtleTf2Broadcaster::pose_callback(const turtlesim::PoseConstPtr& msg)
{
    geometry_msgs::TransformStamped transformStamped;

    transformStamped.header.stamp = ros::Time::now();
    transformStamped.header.frame_id = "world";
    transformStamped.child_frame_id = turtle_name;
    transformStamped.transform.translation.x = msg->x;
    transformStamped.transform.translation.y = msg->y;
    transformStamped.transform.translation.z = 0.0;
    tf2::Quaternion q;
    q.setRPY(0, 0, msg->theta);
    transformStamped.transform.rotation.x = q.x();
    transformStamped.transform.rotation.y = q.y();
    transformStamped.transform.rotation.z = q.z();
    transformStamped.transform.rotation.w = q.w();

    br.sendTransform(transformStamped);
}

void TurtleTf2Broadcaster::process()
{
    ros::spin();
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "turtle_tf2_broadcaster");
    TurtleTf2Broadcaster turtle_tf2_broadcaster;
    turtle_tf2_broadcaster.process();
    return 0;
}
