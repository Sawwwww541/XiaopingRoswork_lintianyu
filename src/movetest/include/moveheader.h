#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>

class Point{
public:
    double x;
    double y;
    double yaw;
};

//枚举小乌龟状态
enum Stage{FORWARD_A,FORWARD_B,SPIN};

extern Stage stage;
extern Point now,A,B;
extern geometry_msgs::Twist vel_msg;
extern ros::Publisher move_pub;

//通过回调函数更新当前坐标
void odometryCallback(const nav_msgs::Odometry::ConstPtr& msg){
    now.x=msg->pose.pose.position.x;
    now.y=msg->pose.pose.position.y;
    now.yaw=msg->pose.pose.orientation.z;
    ROS_INFO("Now odom received pose [x=%f,y=%f]",//校验坐标
             msg->pose.pose.position.x, msg->pose.pose.position.y);
}

void movetoA(){
    //去A点
    if(stage==FORWARD_A){
        vel_msg.linear.x = 0.3;
        vel_msg.angular.z = 0.0;
        move_pub.publish(vel_msg);
        ROS_INFO("Move forward A , now position [%f,%f]",now.x,now.y);
        //到达A点停下
        if(fabs(now.x-A.x)<0.1){
            vel_msg.linear.x = 0.0;
            vel_msg.angular.z = 0.0;
            move_pub.publish(vel_msg);
            ROS_INFO("Stop , velocity commond [%f,%f]",now.x,now.y);
            stage=SPIN;
        }
    }
}

void spin(){
    //顺时针旋转
    if(stage==SPIN){
        vel_msg.linear.x = 0.0;
        vel_msg.angular.z = -0.3;
        move_pub.publish(vel_msg);
        ROS_INFO("Spin , now yaw [%f]",now.yaw);
        if(now.yaw<=-0.75){
            vel_msg.linear.x = 0.0;
            vel_msg.angular.z = 0.0;
            move_pub.publish(vel_msg);
            ROS_INFO("Stop spinning");
            stage=FORWARD_B;
        }

    }
}


void movetoB(){
    //去B点
    if(stage==FORWARD_B){
        vel_msg.linear.x = 0.3;
        vel_msg.angular.z = 0.0;
        move_pub.publish(vel_msg);
        ROS_INFO("Move forward B");
        //到B点停下
        if(fabs(now.y-B.y)<0.1){
            vel_msg.linear.x = 0.0;
            vel_msg.angular.z = 0.0;
            move_pub.publish(vel_msg);
            ROS_INFO("Stop ; Congratulations! You have reached the critical section");
        }
    }
}
