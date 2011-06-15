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

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class telepresenceFrame
///////////////////////////////////////////////////////////////////////////////
class telepresenceFrame : public wxFrame 
{
	private:
		ros::NodeHandle nh_;
		ros::Subscriber image_color;
		wxTimer* update_timer_;

	
	protected:
		wxStaticBitmap* m_bitmap2;
		wxButton* m_button56;
		wxButton* m_button57;
		wxButton* m_button61;
		wxButton* m_button58;
		wxStaticText* m_staticText2;

		void onUpdate(wxTimerEvent& evt);
		void imageColor_callback(const sensor_msgs::ImageConstPtr& msg);
		
		// Virtual event handlers, overide them in your derived class
		virtual void RecvUpKey( wxCommandEvent& event );
		virtual void RecvLeftKey( wxCommandEvent& event );
		virtual void RecvRightKey( wxCommandEvent& event );
		virtual void RecvDownKey( wxCommandEvent& event );
		
	
	public:
		
		telepresenceFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("ui"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		~telepresenceFrame();
	
};

#endif //__ui__
