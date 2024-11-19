#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_listener.h>
#include <cmath>
#include <queue>

class SubGuide{
  public:
    SubGuide():n(),sub(n.subscribe("/path_points", 1, &SubGuide::callback, this)),pub(n.advertise<geometry_msgs::Twist>("/cmd_vel", 10)),Listener(Buffer){};
    void callback(const nav_msgs::PathConstPtr& msg){
      for(auto &pose : msg->poses){
        target.push(pose);
      }
    }
    void run(){
      ros::Rate loop_rate(10);
      while(ros::ok()){
        geometry_msgs::PoseStamped target_pose=target.front();
        try{
          geometry_msgs::TransformStamped tfs=Buffer.lookupTransform("tb3_1/base_link", target_pose.header.frame_id, ros::Time(0));

          double x=tfs.transform.translation.x+target_pose.pose.position.x;
          double y=tfs.transform.translation.y+target_pose.pose.position.y;
          double distance=sqrt(pow(x,2)+pow(y,2));
          double angle=atan2(y,x);

          geometry_msgs::Twist cmd_vel;
          if(fabs(angle)>0.1){
            cmd_vel.angular.z=angle;
          }else if(fabs(x)+fabs(y)>1){
            cmd_vel.angular.z=0;
            cmd_vel.linear.x=0.5*distance;
          }else{
            cmd_vel.angular.z=0;
            cmd_vel.linear.x=0;
            target.pop();
          }
          pub.publish(cmd_vel);
        }
        catch(const std::exception &e){
          ROS_ERROR("Error: %s", e.what());
          }
          ros::spinOnce();
          loop_rate.sleep();
        }
    }


  private:
    ros::NodeHandle n;
    ros::Subscriber sub;
    ros::Publisher pub;
    tf2_ros::Buffer Buffer;
    tf2_ros::TransformListener Listener;
    std::queue<geometry_msgs::PoseStamped> target;
};

int main(int argc, char **argv){
  ros::init(argc, argv, "sub_guide");
  SubGuide sub;
  sub.run();
  return 0;
}
