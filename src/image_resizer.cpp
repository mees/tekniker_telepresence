/*
 * Copyright (C) 2011, José María Martínez Otzeta and Tekniker Technological Center 
 */

#include <image_transport/image_transport.h>
#include <opencv/cv.h>
#include <cv_bridge/cv_bridge.h>

image_transport::Publisher pub_image;

cv::Mat destination;

int hertzs;
int percentage;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
	cv_bridge::CvImagePtr cv_ptr;
	cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
	int new_width = (int)(msg->width * percentage / 100.0);
	int new_height = (int)(msg->height * percentage / 100.0);
	cv::resize(cv_ptr->image, destination, cvSize(new_width, new_height));
	destination.copyTo(cv_ptr->image);
	pub_image.publish(cv_ptr->toImageMsg());
}

int main(int argc, char** argv)
{

  ros::init(argc, argv, "image_resizer");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  pub_image = it.advertise("/image_resized", 1);

	hertzs = 5;
	percentage = 100;

	ROS_WARN("This node admits two arguments\n"
			"The first one is the percentage (integer number) with respect to the source image (100\% by default)\n"
			"The second one is the publishing frequency (hertzs) of the new topic '/image_resized' (5 by default)");

  if (ros::names::remap("/image") == "/image") {
    ROS_WARN("The '/image' topic has not been remapped! The common usage is:\n"
             "\t$ rosrun tekniker_camera image_resizer /image:=<image topic> ");
  }

	if (argc == 1)
		ROS_INFO ("Image is not resized, but frequency of the new topic is now %d Hz", hertzs);
	if (argc >= 2)
	{
		percentage = atoi(argv[1]);
		if (argc == 3) 
			hertzs = atoi(argv[2]);
		ROS_INFO ("Image is resized to a percentage of %d%% in each dimension and the frequency of the new topic is %d Hz", percentage, hertzs);
	}

  ros::Rate loop_rate(hertzs);

	ros::Subscriber sub_rgb = nh.subscribe("/image", 1, imageCallback);

  while (nh.ok()) 
		{
			ros::spinOnce();
			loop_rate.sleep();
		}
}


