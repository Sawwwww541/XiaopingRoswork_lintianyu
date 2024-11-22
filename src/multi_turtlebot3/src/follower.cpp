#include "follower.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "follower");
    Follower follower;
    follower.run();

    return 0;
}