//The follower is turtlebot3_1
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_listener.h>

class Follower {
public:
    Follower():n(),buffer(),listener(buffer),pub(n.advertise<geometry_msgs::Twist>("/tb3_1/cmd_vel",1000)){};
    void run() {
        ros::Rate loop_rate=ros::Rate(10);
        while(ros::ok()){
            try{
                geometry_msgs::TransformStamped tfs=Follower::buffer.lookupTransform("tb3_1/base_link", "tb3_0/base_link", ros::Time(0));
                geometry_msgs::Twist twist,stop;
                twist.linear.x=0.5*sqrt(pow(tfs.transform.translation.x,2)+pow(tfs.transform.translation.y,2));
                twist.angular.z=4*atan2(tfs.transform.translation.y,tfs.transform.translation.x);

                stop.linear.x=0;
                stop.angular.z=0;

                if(fabs(tfs.transform.translation.x)+fabs(tfs.transform.translation.y)>0.5) pub.publish(twist);

                else pub.publish(stop);
            }
            catch(const std::exception& e){
                ROS_ERROR("错误错误错误: %s", e.what());
            }


        }
    }
private:
    ros::NodeHandle n;

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener;

    ros::Publisher pub;

};
