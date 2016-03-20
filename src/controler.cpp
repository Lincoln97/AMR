#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>
#include <iostream>

#define b 0.35
#define r 0.1

void S_calc(std_msgs::Float64 &vr, std_msgs::Float64 &vl,double v, double w){
    vr.data = v - ((b/2)*w);
    vl.data = v + ((b/2)*w);
}
    
int main(int argc, char **argv){
    double v=1, w=0;
    std_msgs::Float64 vr, vl;
    
    ros::init(argc,argv,"control");
    
    ros::NodeHandle control;
    
    ros::Publisher pubR = control.advertise<std_msgs::Float64>("/vrep/vehicle/motorRightSpeed", 1);
    ros::Publisher pubL = control.advertise<std_msgs::Float64>("/vrep/vehicle/motorLeftSpeed", 1);
    
    ros::Rate loop_rate(10);
    while(ros::ok()){
	ROS_INFO("insira v e w");
	std::cin >> v >> w;	
	
	S_calc(vr,vl , v, w);
	pubR.publish(vr);
	pubL.publish(vl);
	
	ros::spinOnce();
	loop_rate.sleep();
    }
}
