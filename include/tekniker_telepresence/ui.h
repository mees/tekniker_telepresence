///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ui__
#define __ui__

#define SINFOV 0.520264473

#include <ros/ros.h>
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <cv_bridge/CvBridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Int32.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "tekniker_telepresence/camview.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/Twist.h>
#include "segway_rmp/Status.h"
#include "tekniker_kinect/depth_server.h"
#include <joy/Joy.h>

#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/event.h>
#include <wx/checkbox.h>
#include <wx/thread.h>
#include <wx/gauge.h>


///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class telepresenceFrame
///////////////////////////////////////////////////////////////////////////////

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class telepresenceFrame : public wxFrame, public wxThreadHelper
{
	private:
		ros::NodeHandle nh_;
		image_transport::Subscriber image_color;
		ros::Subscriber status;
		ros::ServiceClient client;
		ros::Publisher my_webcam;
		ros::Publisher vel_pub;
		ros::Publisher goal_pub;
		ros::Subscriber joy_sub_;
		image_transport::Publisher image_pub_;
		image_transport::ImageTransport *it_;
		wxTimer* update_timer_;
		wxTimer* checkGoal_timer;
		wxTimer* goalUp_timer;
		wxTimer* goalDown_timer;
		wxTimer* goalLeft_timer;
		wxTimer* goalRight_timer;
		wxGauge* prgBar;
		geometry_msgs::Twist vel;
		sensor_msgs::CvBridge bridge;
		int linear_, angular_;
		double l_scale_, a_scale_;
		bool ps3joy_activated;
		ros::Time begin;
		ros::Time end;
		ros::Time begin2;
		ros::Time end2;
		

	
	protected:
		wxBitmap m_bitmap2;
		wxBitmap m_bitmap;
		wxButton* m_button56;
		wxButton* m_button57;
		wxButton* m_button61;
		wxButton* m_button58;
		wxStaticText* m_staticText2;
		wxCheckBox* m_checkbox;
		int m_nWidth;
		int m_nHeight;
		CCamView*	m_pCameraView;
		CCamView*	m_pCameraView2;
		IplImage _IplImg;
		IplImage *_IplImg2;
		geometry_msgs::PoseStamped goal;
		MoveBaseClient* ac;
		wxMutex s_mutex;
		wxCriticalSection cs;
		IplImage *PointCloud_image;
		CvScalar s;
		int my;
		int mx;
		bool changed;



		void onUpdate(wxTimerEvent& evt);
		void sendGoalUp(wxTimerEvent& evt);
		void sendGoalDown(wxTimerEvent& evt);
		void sendGoalRight(wxTimerEvent& evt);
		void sendGoalLeft(wxTimerEvent& evt);
		void OnClose(wxCloseEvent& evt);
		void imageColor_callback(const sensor_msgs::ImageConstPtr& msg);
		void imageDepth_callback(const sensor_msgs::ImageConstPtr& msg);
		void status_callback(const segway_rmp::Status& msg);
		void coordX_callback(const std_msgs::Int32ConstPtr& msg);
		void coordY_callback(const std_msgs::Int32ConstPtr& msg);
		void joyCallback(const joy::Joy::ConstPtr& joy);
		
		// Virtual event handlers, overide them in your derived class
		virtual void RecvUpKeyPress(wxCommandEvent& event);
		virtual void RecvUpKeyRelease(wxCommandEvent& event);
		virtual void RecvDownKeyPress(wxCommandEvent& event);
		virtual void RecvDownKeyRelease(wxCommandEvent& event);
		virtual void RecvLeftKeyPress(wxCommandEvent& event);
		virtual void RecvLeftKeyRelease(wxCommandEvent& event);
		virtual void RecvRightKeyPress(wxCommandEvent& event);
		virtual void RecvRightKeyRelease(wxCommandEvent& event);
		virtual void RecvRightKeyPressOnImage(wxCommandEvent& event);

		virtual wxThread::ExitCode Entry();
		void OnThreadUpdate(wxCommandEvent& evt);
		DECLARE_EVENT_TABLE();
		
	
	public:
		
		telepresenceFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ui"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~telepresenceFrame();
		
};

#endif //__ui__
