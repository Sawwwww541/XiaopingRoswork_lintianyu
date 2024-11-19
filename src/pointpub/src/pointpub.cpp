#include<ros/ros.h>
#include<nav_msgs/Odometry.h>
#include<nav_msgs/Path.h>
#include<geometry_msgs/PoseStamped.h>
#include<vector>

class PointPub{
  public:
    PointPub():n(),sub(n.subscribe("/tb3_0/odom", 10, &PointPub::callback, this)),path_pub(n.advertise<geometry_msgs::PoseStamped>("/path_points", 10)){};
    void callback(const nav_msgs::Odometry::ConstPtr& msg){
      geometry_msgs::PoseStamped pose;
      pose.header=msg->header;
      pose.pose=msg->pose.pose;

      path_points.push_back(pose);
    }
    void run(){
      ros::Rate loop_rate(10);
      while(ros::ok()){
        nav_msgs::Path path;
        path.header.stamp=ros::Time::now();
        path.header.frame_id="map";
        path.poses=path_points;

        path_pub.publish(path);

        ros::spinOnce();
        loop_rate.sleep();
      }
    }
  private:
    ros::NodeHandle n;

    ros::Subscriber sub;
    ros::Publisher path_pub;

    std::vector<geometry_msgs::PoseStamped> path_points;
};

int main(int argc, char **argv){
  ros::init(argc, argv, "pointpub");
  PointPub pub;
  pub.run();

}