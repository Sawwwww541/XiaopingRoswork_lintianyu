#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2/LinearMath/Quaternion.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/TransformStamped.h>

std::string botname="tb3_0";

void OdomCallback(const nav_msgs::Odometry::ConstPtr& msg){
  static tf2_ros::TransformBroadcaster br;
  geometry_msgs::TransformStamped tfs;

  tfs.header.frame_id = "odom";
  tfs.header.stamp = ros::Time::now();

  tfs.child_frame_id = botname+"/base_footprint";

  tfs.transform.translation.x = msg->pose.pose.position.x;
  tfs.transform.translation.y = msg->pose.pose.position.y;
  tfs.transform.translation.z = msg->pose.pose.position.z;

  tfs.transform.rotation.x = msg->pose.pose.orientation.x;
  tfs.transform.rotation.y = msg->pose.pose.orientation.y;
  tfs.transform.rotation.z = msg->pose.pose.orientation.z;
  tfs.transform.rotation.w = msg->pose.pose.orientation.w;

  br.sendTransform(tfs);

}

int main(int argc, char **argv){
  ros::init(argc, argv, "connect_tf_tree");
  ros::NodeHandle n;

  botname=argv[1];

	ros::Subscriber sub=n.subscribe(botname+"/odom",1000,OdomCallback);

  ros::spin();

  return 0;

  }