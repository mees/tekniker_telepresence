///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __ui__
#define __ui__

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

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class telepresenceFrame
///////////////////////////////////////////////////////////////////////////////
class telepresenceFrame : public wxFrame 
{
	private:
	
	protected:
		wxStaticBitmap* m_bitmap2;
		wxButton* m_button56;
		wxButton* m_button57;
		wxButton* m_button61;
		wxButton* m_button58;
		wxStaticText* m_staticText2;
		
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
