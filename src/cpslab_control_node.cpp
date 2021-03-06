#include "stdafx.h"
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "math.h"

std_msgs::Float64 r1x, r1y, r1z;
std_msgs::Float64 r2x, r2y, r2z;
geometry_msgs::Twist cmd;

void chatterCallback(const nav_msgs::Odometry::ConstPtr& dptr);
void chatterCallback2(const nav_msgs::Odometry::ConstPtr& dptr);


int main(int argc, char **argv){
	ros::init(argc, argv, "cpslab_control");
	ros::NodeHandle n;
	ros::Publisher pub1 = n.advertise<geometry_msgs::Twist>("cmd_vel/robot1", 1000);
	ros::Subscriber sub = n.subscribe("p3dx/base_pose_ground_truth", 1000, chatterCallback);		
	ros::Subscriber sub2 = n.subscribe("p3dx2/base_pose_ground_truth", 1000, chatterCallback2);	

	ros::Rate loop_rate(2);
	while(ros::ok()){	

		int i=0;
		if(r1x.data > r2x.data){i=-1;}else{i=1;}
		ROS_INFO("x1:%f, x2:%f, i:%d", r1x.data, r2x.data, i);
	
		cmd.linear.x = 0.5*pow(-1,r1x.data > r2x.data);
		cmd.angular.z = 0;		
		pub1.publish(cmd);

		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}
	

	

void chatterCallback(const nav_msgs::Odometry::ConstPtr& dptr){
	r1x.data = dptr->pose.pose.position.x;
	r1y.data = dptr->pose.pose.position.y;
	r1z.data = dptr->pose.pose.position.z;
	ROS_INFO("x1:%f, x2:%f", r1x.data, r2x.data);
	
}


void chatterCallback2(const nav_msgs::Odometry::ConstPtr& dptr){
	r2x.data = dptr->pose.pose.position.x;
	r2y.data = dptr->pose.pose.position.y;
	r2z.data = dptr->pose.pose.position.z;
}

