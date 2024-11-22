//The follower is turtlebot3_1
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf/LinearMath/Matrix3x3.h>
#include <tf2_ros/transform_listener.h>

class Follower {
public:
    Follower():n(),buffer(),listener(buffer),
    pub(n.advertise<geometry_msgs::Twist>("/tb3_1/cmd_vel",1000)),
    distance(0.0),state(forward){};
    void run() {
        ros::Rate loop_rate=ros::Rate(10);
        while(ros::ok()){
            try{
                geometry_msgs::TransformStamped tfs=Follower::buffer.lookupTransform("tb3_1/base_link", "tb3_0/base_link", ros::Time(0));
                geometry_msgs::Twist twist,stop,spin;

                /*值得注意的是，当我们把包含tfs数据的表达式的计算结果赋值给速度，小乌龟的行为会变得不可控，例如，如果我们令：
                 *distance=sqrt(pow(tfs.transform.translation.x,2)+pow(tfs.transform.translation.y,2));
                 *linear.x=0.5*distance;
                 * 此时当我们发布这条速度指令，小乌龟tb3——1会做出伪跟随动作，即在第一个转弯点朝向tb3——0前进，在抵达第二个转弯点前会失控，即使我们并没有
                 * 为小乌龟tb3——1赋任何的角速度，小乌龟仍会发生旋转；
                 * 同样的，当我们只赋给角速度一个包含tfs数据的表达式时，小乌龟也会失控；
                 * 对于这种现象，目前我认为可能是乌龟两侧轮子间的性能不同，在速度急剧变化时产生差速，从而发生旋转
                 * 想解决这个问题，要么改进控制器为PID，要么直接赋数字，而非一个表达式（P控制器）
                 */

                /*失控的主要原因还是速度的急剧变化以及轮子间的性能有差，与其是否为P控制器无关，但P控制器在大部分情况下波动较大，其不稳定的特质，导致了失控*/

                twist.linear.x=0.1;
                twist.angular.z=0.0;

                stop.linear.x=0.0;
                stop.angular.z=0.0;

                spin.linear.x=0.0;
                spin.angular.z=0.2*tfs.transform.translation.y;

                distance=sqrt(pow(tfs.transform.translation.x,2)+pow(tfs.transform.translation.y,2));

                ROS_INFO("tfs.x=%f , tfs.y=%f , distance=%f",tfs.transform.translation.x,tfs.transform.translation.y,distance);
                if(fabs(tfs.transform.translation.x)+fabs(tfs.transform.translation.y)>1.0) {

                    if(tfs.transform.translation.x<0.01&&(distance-tfs.transform.translation.x>0.01)){
                        state=spinning;
                }else if(distance-tfs.transform.translation.x<0.01) state=forward;
                    if(state==forward) pub.publish(twist);
                    if(state==spinning) pub.publish(spin);
                }else pub.publish(stop);


            }
            catch(const std::exception& e){
                ROS_INFO("错误错误错误: %s", e.what());
            }


        }
    }
private:
    ros::NodeHandle n;

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener;

    ros::Publisher pub;

    enum State {spinning,forward};
    State state;

    double distance;
};
