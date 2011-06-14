///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2009)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "tekniker_telepresence/ui.h"

///////////////////////////////////////////////////////////////////////////

telepresenceFrame::telepresenceFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 800,600 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	bSizer1->SetMinSize( wxSize( 800,600 ) ); 
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	m_bitmap2 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_bitmap2, 1, wxALL|wxEXPAND, 5 );
	
	bSizer1->Add( bSizer4, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxVERTICAL );
	
	m_button56 = new wxButton( this, wxID_ANY, wxT("Up"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer32->Add( m_button56, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button57 = new wxButton( this, wxID_ANY, wxT("Left"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer35->Add( m_button57, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer38->Add( bSizer35, 1, wxEXPAND, 5 );
	
	m_button61 = new wxButton( this, wxID_ANY, wxT("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer38->Add( m_button61, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	bSizer37->Add( bSizer38, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	
	m_button58 = new wxButton( this, wxID_ANY, wxT("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer36->Add( m_button58, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	bSizer37->Add( bSizer36, 1, wxEXPAND, 5 );
	
	bSizer33->Add( bSizer37, 1, wxEXPAND, 5 );
	
	bSizer32->Add( bSizer33, 1, wxEXPAND, 5 );
	
	bSizer28->Add( bSizer32, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Robot Status"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer39->Add( m_staticText2, 0, wxALL, 5 );
	
	bSizer28->Add( bSizer39, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer28, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	// Connect Events
	m_button56->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvUpKey ), NULL, this );
	m_button57->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvLeftKey ), NULL, this );
	m_button61->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvRightKey ), NULL, this );
	m_button58->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvDownKey ), NULL, this );
}
		public void RecvUpKey( wxCommandEvent& event )
		{
			printf("RecvUpKey");
		}
		public void RecvLeftKey( wxCommandEvent& event )
		{
			printf("RecvLeftKey");
		}
		public void RecvRightKey( wxCommandEvent& event )
		{
			printf("RecvRightKey");
		}
		public void RecvDownKey( wxCommandEvent& event )
		{
			printf("RecvDownKey");
		}

telepresenceFrame::~telepresenceFrame()
{
	// Disconnect Events
	m_button56->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvUpKey ), NULL, this );
	m_button57->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvLeftKey ), NULL, this );
	m_button61->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvRightKey ), NULL, this );
	m_button58->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvDownKey ), NULL, this );
}
