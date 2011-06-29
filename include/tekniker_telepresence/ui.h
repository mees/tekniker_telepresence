///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ui__
#define __ui__

#include <ros/ros.h>
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Int32.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "tekniker_telepresence/camview.h"
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_broadcaster.h>


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
#include <wx/thread.h>


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
		ros::Publisher my_webcam;
		image_transport::Publisher image_pub_;
		image_transport::ImageTransport *it_;
		wxTimer* update_timer_;
		wxTimer* checkGoal_timer;

	
	protected:
		wxBitmap m_bitmap2;
		wxBitmap m_bitmap;
		wxButton* m_button56;
		wxButton* m_button57;
		wxButton* m_button61;
		wxButton* m_button58;
		wxStaticText* m_staticText2;
		int m_nWidth;
		int m_nHeight;
		CCamView*	m_pCameraView;
		CCamView*	m_pCameraView2;
		//wxCriticalSection mutex;
		IplImage _IplImg;
		IplImage *_IplImg2;
		move_base_msgs::MoveBaseGoal goal;
		MoveBaseClient* ac;//("move_base", true);


		void onUpdate(wxTimerEvent& evt);
		void checkGoalState(wxTimerEvent& evt);
		void OnClose(wxCloseEvent& evt);
		void imageColor_callback(const sensor_msgs::ImageConstPtr& msg);
		void coordX_callback(const std_msgs::Int32ConstPtr& msg);
		void coordY_callback(const std_msgs::Int32ConstPtr& msg);
		
		// Virtual event handlers, overide them in your derived class
		virtual void RecvUpKey( wxCommandEvent& event );
		virtual void RecvLeftKey( wxCommandEvent& event );
		virtual void RecvRightKey( wxCommandEvent& event );
		virtual void RecvDownKey( wxCommandEvent& event );
		virtual wxThread::ExitCode Entry();
		void OnThreadUpdate(wxCommandEvent& evt);
		DECLARE_EVENT_TABLE();
		
	
	public:
		
		telepresenceFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ui"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~telepresenceFrame();
		
};

#endif //__ui__
