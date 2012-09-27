#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include <image_transport/image_transport.h>
#include "tekniker_kinect/depth_server.h"
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/CvBridge.h>
#include <cv_bridge/cv_bridge.h>



IplImage *PointCloud_image=NULL;

bool get_depth(tekniker_kinect::depth_server::Request  &req,
         tekniker_kinect::depth_server::Response &res )
{
	CvScalar s;
	float tmp=0;
	int count=0;
	try{
		if((req.x>5 && req.y>5) && (req.x<635 &&req.y<475))
		{
			for (int a=req.y-5;a<req.y+5;a++)
			{
				for (int b=req.x-5;b<req.x+5;b++)
				{
					if(PointCloud_image==NULL)
					{
						printf("global var PointCloud_image==NULL\n");
					}
					//printf("aldagai globala atzituko dut...\n");
					s=cvGet2D(PointCloud_image,a ,b);
					//printf("atzitu dut!\n");
					if (s.val[0]!=s.val[0])
					{
						printf("s.val[0]!=s.val[0]\n");
						s.val[0]  = 0;
					}
					else
					{
					tmp=tmp+s.val[0];
					count++;
					}
				}
			}
			if (count==0)
			{
				res.depth=0;
			}
			else
			{
				res.depth=tmp/count;
			}
		}
		else
		{
			printf("ertzetan klikatu dezu!\n");
			res.depth=0;
		}
		
	}catch(cv::Exception& e)
	{
		printf("exception\n");
	}
  	ROS_INFO("request: x=%ld, y=%ld", (long int)req.x, (long int)req.y);
	ROS_INFO("sending back response: [%ld]", (long int)res.depth);
    return true;
}
void imageDepth_callback(const sensor_msgs::ImageConstPtr& msg)
{
	sensor_msgs::CvBridge bridge;
	
	IplImage *aux=NULL;
	aux = bridge.imgMsgToCv(msg, msg->encoding.c_str());
	cvCopy(aux, PointCloud_image);
	
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "get_kinect_depth");
  ros::NodeHandle n;
  image_transport::ImageTransport *it_;
  it_=new image_transport::ImageTransport(n);
  image_transport::Subscriber image_depth = it_->subscribe("/camera/depth/image", 1, imageDepth_callback);

  PointCloud_image=cvCreateImage(cvSize(640,480),IPL_DEPTH_32F,1);
  ros::ServiceServer service = n.advertiseService("get_kinect_depth", get_depth);
  ROS_INFO("Get x,y depth from kinect.");
  ros::spin();

  return 0;
}
