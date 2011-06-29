/*
 * Copyright (C) 2011, Oier Mees and Technological Center Tekniker
 */
#include "tekniker_telepresence/ui.h"
#include <cstdlib>
#include <ctime>

namespace enc = sensor_msgs::image_encodings;

static const double pi = 3.14159265358979323846;

DECLARE_EVENT_TYPE(wxEVT_COMMAND_MYTHREAD_UPDATE, -1)
DEFINE_EVENT_TYPE(wxEVT_COMMAND_MYTHREAD_UPDATE)
BEGIN_EVENT_TABLE(telepresenceFrame, wxFrame)
	EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_MYTHREAD_UPDATE, telepresenceFrame::OnThreadUpdate)
END_EVENT_TABLE()

//tell the action client that we want to spin a thread by default

telepresenceFrame::telepresenceFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	//ShowFullScreen(true);
	this->SetSizeHints( wxSize( 1100,700 ), wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	//bSizer1->SetMinSize( wxSize( 900,700 ) ); 
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkbox = new wxCheckBox(this, wxID_ANY, wxT("Navigation On?"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkbox->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
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
	bSizer1->Add( bSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
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
	bSizer39 = new wxBoxSizer( wxHORIZONTAL );
	
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Robot Status"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	bSizer39->Add( m_checkbox, 0, wxALL, 5 );
	//bSizer39->Add( m_staticText2, 0, wxALL, 5 );
	
	bSizer28->Add( bSizer39, 1, wxEXPAND, 5 );
	
	bSizer1->Add( bSizer28, 0, wxEXPAND, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	

	it_=new image_transport::ImageTransport(nh_);
	//image_pub_ = it_->advertise("out", 1);
	image_pub_ = it_->advertise("/mywebcam", 1);
	image_color = it_->subscribe("/camera/rgb/image_color", 1, &telepresenceFrame::imageColor_callback, this);
	ac= new MoveBaseClient("move_base", true);
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
    
    checkGoal_timer=new wxTimer(this);
    Connect(checkGoal_timer->GetId(), wxEVT_TIMER, wxTimerEventHandler(telepresenceFrame::checkGoalState), NULL, this);
    //while(!ac->waitForServer(ros::Duration(5.0))){
    //ROS_INFO("Waiting for the move_base action server to come up");
  //}


}
void telepresenceFrame::checkGoalState(wxTimerEvent& evt)
{
	actionlib::SimpleClientGoalState aux=ac->getState();
	if(aux!=actionlib::SimpleClientGoalState::PENDING && aux!=actionlib::SimpleClientGoalState::ACTIVE)
	{
		if(aux == actionlib::SimpleClientGoalState::SUCCEEDED)
			ROS_INFO("He llegado correctamente al objetivo");
        else
            ROS_INFO("No he conseguido llegar al objetivo");
        checkGoal_timer->Stop();
	}
	else
	{
		printf("pending edo active dago\n");
	}
}
	
void telepresenceFrame::RecvUpKey( wxCommandEvent& event )
{
	printf("RecvUpKey");
	btQuaternion quat;
    quat.setRPY(0.0, 0.0, 0);
    tf::quaternionTFToMsg(quat,goal.target_pose.pose.orientation);
	goal.target_pose.header.stamp=ros::Time::now();
	goal.target_pose.header.frame_id = "/base_link";
	goal.target_pose.pose.position.x = 1;
    goal.target_pose.pose.position.y = 0;
    goal.target_pose.pose.position.z = 0;

	ros::spinOnce();

               if (ros::Time::now().toSec() - goal.target_pose.header.stamp.toSec() < 2)
               {
                       goal.target_pose.header.stamp = ros::Time::now();
                       ROS_INFO("Sending goal");

                       ac->sendGoal(goal);
                      checkGoal_timer->Start(500);
               }
               else
                       ROS_INFO("El objetivo es demasiado antiguo, no se intentará");
}

void telepresenceFrame::RecvLeftKey( wxCommandEvent& event )
{
	printf("RecvLeftKey");
	btQuaternion quat;
    quat.setRPY(0.0, 0.0, pi/2);
    tf::quaternionTFToMsg(quat,goal.target_pose.pose.orientation);
    
    goal.target_pose.header.stamp=ros::Time::now();
	goal.target_pose.header.frame_id = "/base_link";
	goal.target_pose.pose.position.x = 0;
    goal.target_pose.pose.position.y = 0;
    goal.target_pose.pose.position.z = 0;

	ros::spinOnce();

               if (ros::Time::now().toSec() - goal.target_pose.header.stamp.toSec() < 2)
               {
                       goal.target_pose.header.stamp = ros::Time::now();
                       ROS_INFO("Sending goal");

                       ac->sendGoal(goal);
                      checkGoal_timer->Start(500);
               }
               else
                       ROS_INFO("El objetivo es demasiado antiguo, no se intentará");

}

void telepresenceFrame::RecvRightKey( wxCommandEvent& event )
{
	printf("RecvRightKey");
		btQuaternion quat;
    quat.setRPY(0.0, 0.0, -pi/2);
    tf::quaternionTFToMsg(quat,goal.target_pose.pose.orientation);
    
    goal.target_pose.header.stamp=ros::Time::now();
	goal.target_pose.header.frame_id = "/base_link";
	goal.target_pose.pose.position.x = 0;
    goal.target_pose.pose.position.y = 0;
    goal.target_pose.pose.position.z = 0;

	ros::spinOnce();

               if (ros::Time::now().toSec() - goal.target_pose.header.stamp.toSec() < 2)
               {
                       goal.target_pose.header.stamp = ros::Time::now();
                       ROS_INFO("Sending goal");

                       ac->sendGoal(goal);
                      checkGoal_timer->Start(500);
               }
               else
                       ROS_INFO("El objetivo es demasiado antiguo, no se intentará");
}

void telepresenceFrame::RecvDownKey( wxCommandEvent& event )
{
	printf("RecvDownKey");
    btQuaternion quat;
    quat.setRPY(0.0, 0.0, 0);
    tf::quaternionTFToMsg(quat,goal.target_pose.pose.orientation);
    goal.target_pose.header.stamp=ros::Time::now();
	goal.target_pose.header.frame_id = "/base_link";
	goal.target_pose.pose.position.x = -1;
    goal.target_pose.pose.position.y = 0;
    goal.target_pose.pose.position.z = 0;

	ros::spinOnce();

               if (ros::Time::now().toSec() - goal.target_pose.header.stamp.toSec() < 2)
               {
                       goal.target_pose.header.stamp = ros::Time::now();
                       ROS_INFO("Sending goal");

                       ac->sendGoal(goal);
                      checkGoal_timer->Start(500);
               }
               else
                       ROS_INFO("El objetivo es demasiado antiguo, no se intentará");
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
	delete checkGoal_timer;
	delete m_pCameraView;
	delete m_pCameraView2;
	if(it_!=NULL)
		delete it_;
	if(ac!=NULL)
		delete ac;
	if (GetThread() && GetThread()->IsRunning())
	{
		printf("deleta thread\n");
		GetThread()->Delete();
	}//cv::destroyWindow(WINDOW);
}
