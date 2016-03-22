#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Twist.h>
#include <iostream>

#define b 0.35
#define r 0.1

float v, w;

void S_calc(std_msgs::Float32 &vr, std_msgs::Float32 &vl,double v, double w){
    vl.data = v - ((b/2)*w);
    vr.data = v + ((b/2)*w);
}

void callback(const geometry_msgs::TwistConstPtr &msg){
    v = msg->linear.x;
    w = msg->angular.z;
}
    
int main(int argc, char **argv){
    
    std_msgs::Float32 vr, vl;
    
    ros::init(argc,argv,"controla");
    
    ros::NodeHandle controla;
    
    ros::Subscriber v_sub = controla.subscribe("carrot_velocity", 1, callback);
    //ros::Subscriber v_sub = control2.subscribe("left_sonar", 1, callback);
    //ros::Subscriber v_sub = control2.subscribe("right_sonar", 1, callback);
    
    ros::Publisher pubR = controla.advertise<std_msgs::Float32>("/vrep/vehicle/motorRightSpeed", 1);
    ros::Publisher pubL = controla.advertise<std_msgs::Float32>("/vrep/vehicle/motorLeftSpeed", 1);
    
    ros::Rate loop_rate(30);
    while(ros::ok()){
	
	S_calc(vr,vl , v, w);
	pubR.publish(vr);
	pubL.publish(vl);
	
	ros::spinOnce();
	loop_rate.sleep();
    }
}
