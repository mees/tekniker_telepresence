/*
 * Copyright (C) 2011, Oier Mees and Technological Center Tekniker
 */
#include "tekniker_telepresence/ui.h"
#include <cstdlib>
#include <ctime>

namespace enc = sensor_msgs::image_encodings;


int RGBcoordX, RGBcoordY;

DECLARE_EVENT_TYPE(wxEVT_COMMAND_MYTHREAD_UPDATE, -1)
DEFINE_EVENT_TYPE(wxEVT_COMMAND_MYTHREAD_UPDATE)
BEGIN_EVENT_TABLE(telepresenceFrame, wxFrame)
	EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_MYTHREAD_UPDATE, telepresenceFrame::OnThreadUpdate)
END_EVENT_TABLE()
        
telepresenceFrame::telepresenceFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	//ShowFullScreen(true);
	this->SetSizeHints( wxSize( 1400,800 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	//bSizer1->SetMinSize( wxSize( 900,700 ) ); 
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	

	int width, height;
	this->GetClientSize(&width, &height);
	//printf("width:%d,height:%d\n",width,height);

	m_pCameraView = new CCamView(this, wxPoint(5,15), wxSize(640, 480));
	
	m_pCameraView2 = new CCamView( this, wxPoint(0,0), wxSize(400, 300));
	// display my stuff
	SetAutoLayout( TRUE );
	/////////////////////////////////////////////////////
	bSizer4->Add( m_pCameraView, 0, wxALIGN_CENTER_HORIZONTAL, 0);
	bSizer4->Add( m_pCameraView2, 0,wxALIGN_RIGHT, 0);

	if (wxThreadHelper::Create(wxTHREAD_DETACHED) != wxTHREAD_NO_ERROR)
	{
		wxLogError(wxT("Could not create the worker thread!"));
		return;
	}
	if (GetThread()->Run() != wxTHREAD_NO_ERROR)
	{
		wxLogError(wxT("Could not run the worker thread!"));
		return;
	}
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
	

	it_=new image_transport::ImageTransport(nh_);
	//image_pub_ = it_->advertise("out", 1);
	image_pub_ = it_->advertise("/mywebcam", 1);
	image_color = it_->subscribe("/camera/rgb/image_color", 1, &telepresenceFrame::imageColor_callback, this);
	//cv::namedWindow(WINDOW);
	
	// Connect Events
	m_button56->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvUpKey ), NULL, this );
	m_button57->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvLeftKey ), NULL, this );
	m_button61->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvRightKey ), NULL, this );
	m_button58->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvDownKey ), NULL, this );
	
	srand(time(NULL));

    update_timer_ = new wxTimer(this);
    update_timer_->Start(16);

   Connect(update_timer_->GetId(), wxEVT_TIMER, wxTimerEventHandler(telepresenceFrame::onUpdate), NULL, this);
}

	
void telepresenceFrame::RecvUpKey( wxCommandEvent& event )
{
	printf("RecvUpKey");
}

void telepresenceFrame::RecvLeftKey( wxCommandEvent& event )
{
	printf("RecvLeftKey");
}

void telepresenceFrame::RecvRightKey( wxCommandEvent& event )
{
	printf("RecvRightKey");
}

void telepresenceFrame::RecvDownKey( wxCommandEvent& event )
{
	printf("RecvDownKey");
}
void telepresenceFrame::onUpdate(wxTimerEvent& evt)
{
  ros::spinOnce();

  if (!ros::ok())
  {
    Close();
  }
} 


void telepresenceFrame::OnThreadUpdate(wxCommandEvent& evt)
{

	m_pCameraView2->DrawCam(_IplImg2);
	cv::Mat aux(_IplImg2);
	cv_bridge::CvImage cv_ptr2;
	//cv_ptr2->header=aux.header;
	cv_ptr2.encoding=sensor_msgs::image_encodings::RGB8;
	cv_ptr2.image=aux;

	image_pub_.publish(cv_ptr2.toImageMsg());
}
	
void telepresenceFrame::imageColor_callback(const sensor_msgs::ImageConstPtr& msg)
{
/*rosmsg show sensor_msgs/Image
Header header
  uint32 seq
  time stamp
  string frame_id
uint32 height
uint32 width
string encoding
uint8 is_bigendian
uint32 step
uint8[] data*/
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, enc::RGB8);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
	//if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
			//{
				//if (RGBcoordX >= 0 && RGBcoordY >= 0)
					//{
				//cv::circle(cv_ptr->image, cv::Point(RGBcoordX, RGBcoordY), 50, CV_RGB(255,0,0), 3, 8, 0);
				//cv::line(cv_ptr->image, cv::Point(RGBcoordX - 70, RGBcoordY), cv::Point(RGBcoordX + 70, RGBcoordY), CV_RGB(255,0,0), 3, 8, 0);					
				//cv::line(cv_ptr->image, cv::Point(RGBcoordX, RGBcoordY - 70), cv::Point(RGBcoordX, RGBcoordY + 70), CV_RGB(255,0,0), 3, 8, 0);	
					//}
			//}
	
	//cv::imshow(WINDOW, cv_ptr->image);
	//image_pub_.publish(cv_ptr->toImageMsg());
	//printf("imagecolorcallback: width:%d height:%d\n",cv_ptr->image.cols, cv_ptr->image.rows);
	_IplImg=cv_ptr->image;
	//IplImage aux=cv_ptr->image;
	//_IplImg=aux;
	////cvConvertImage(&aux, &_IplImg, CV_CVTIMG_FLIP);
	////printf("imagecolorcallback2: width:%d height:%d\n",_IplImg.width, _IplImg.height);
	//cvFlip(&aux,&_IplImg,1);
	m_pCameraView->DrawCam(&_IplImg);
	
  //ROS_INFO("I heard: [%d]", msg->data[0]);
}

 wxThread::ExitCode telepresenceFrame::Entry()
        {
            CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
            cvSetCaptureProperty(capture,CV_CAP_PROP_CONVERT_RGB, false);
			if ( !capture ) 
			{
				fprintf( stderr, "ERROR: capture is NULL \n" );
				//getchar();
			}
            while (!GetThread()->TestDestroy())
            {
                // since this Entry() is implemented in MyFrame context we don't
                // need any pointer to access the m_data, m_processedData, m_dataCS
                // variables... very nice!

				//{
				//wxCriticalSectionLocker lock(mutex);
				IplImage *aux=cvQueryFrame( capture );
				_IplImg2=aux;
				cvConvertImage(aux,_IplImg2,CV_CVTIMG_SWAP_RB);
				//}
				wxCommandEvent evt(wxEVT_COMMAND_MYTHREAD_UPDATE, wxID_ANY);
	            this->AddPendingEvent(evt);

			}
			cvReleaseCapture( &capture );

                //// VERY IMPORTANT: do not call any GUI function inside this
                ////                 function; rather use wxQueueEvent():
                //wxQueueEvent(this, new wxThreadEvent(wxEVT_COMMAND_MYTHREAD_UPDATE));
                    //// we used pointer 'this' assuming it's safe; see OnClose()


            // TestDestroy() returned true (which means the main thread asked us
            // to terminate as soon as possible) or we ended the long task...
            printf("2.haria amaituko dugu\n");
            return (wxThread::ExitCode)0;
        }


telepresenceFrame::~telepresenceFrame()
{
	// Disconnect Events
	m_button56->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvUpKey ), NULL, this );
	m_button57->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvLeftKey ), NULL, this );
	m_button61->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvRightKey ), NULL, this );
	m_button58->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( telepresenceFrame::RecvDownKey ), NULL, this );
	delete update_timer_;
	delete m_pCameraView;
	delete m_pCameraView2;
	if(it_!=NULL)
		delete it_;
	if (GetThread() && GetThread()->IsRunning())
	{
		printf("deleta thread\n");
		GetThread()->Delete();
	}//cv::destroyWindow(WINDOW);
}
