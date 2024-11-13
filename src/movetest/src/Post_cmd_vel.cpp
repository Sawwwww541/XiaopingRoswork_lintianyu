#include "moveheader.h"

Stage stage=FORWARD_A;//枚举实例

Point now;//实例化当前坐标和两个目标坐标
Point A={0.55,-0.49,0.0};
Point B={0.55,-1.62,0.0};

geometry_msgs::Twist vel_msg;

ros::Publisher move_pub;

bool isgetA=false, isgetB=false;

int main(int argc, char **argv) {

  ros::init(argc, argv, "post_cmd_vel");
  ros::NodeHandle n;
  move_pub=n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
  ros::Subscriber odom_sub=n.subscribe("/odom",10,odometryCallback);
  ros::Rate loop_rate(10);

  while(ros::ok()){
    movetoA();

    spin();

    movetoB();

    loop_rate.sleep();
    ros::spinOnce();

  }

}
