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
int a =0;
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

	prgBar= new wxGauge(this,  wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL,  wxDefaultValidator, wxT("Battery"));
	prgBar->SetValue(70);
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Battery"), wxDefaultPosition, wxDefaultSize, 0 );
	//m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	
	bSizer39->Add( m_checkbox, 0, wxALL, 5 );
	bSizer40->Add( m_staticText2, 0, wxALL, 5 );
	bSizer40->Add( prgBar, 0, wxALL, 5 );
	
	bSizer39->Add(bSizer40,0,wxEXPAND,5);

	bSizer28->Add( bSizer39, 1, wxEXPAND, 5 );

	bSizer1->Add( bSizer28, 0, wxEXPAND, 5 );

	this->SetSizer( bSizer1 );
	this->Layout();

	changed=false;
	mx=0;
	my=0;

	it_=new image_transport::ImageTransport(nh_);
	//image_pub_ = it_->advertise("out", 1);
	image_pub_ = it_->advertise("/mywebcam", 1);
	image_color = it_->subscribe("/camera/rgb/image_color", 1, &telepresenceFrame::imageColor_callback, this);
	image_depth = it_->subscribe("/camera/depth/image", 1, &telepresenceFrame::imageDepth_callback, this);
	ac= new MoveBaseClient("move_base", true);
	vel_pub = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 10);
	//cv::namedWindow(WINDOW);
	// Connect Events
	m_button56->Connect( wxEVT_LEFT_DOWN, wxCommandEventHandler( telepresenceFrame::RecvUpKeyPress ), NULL, this );
	m_button56->Connect( wxEVT_LEFT_UP, wxCommandEventHandler( telepresenceFrame::RecvUpKeyRelease ), NULL, this );

	m_button58->Connect( wxEVT_LEFT_DOWN, wxCommandEventHandler( telepresenceFrame::RecvDownKeyPress ), NULL, this );
	m_button58->Connect( wxEVT_LEFT_UP, wxCommandEventHandler( telepresenceFrame::RecvDownKeyRelease ), NULL, this );
	
	m_button57->Connect( wxEVT_LEFT_DOWN, wxCommandEventHandler( telepresenceFrame::RecvLeftKeyPress ), NULL, this );
	m_button57->Connect( wxEVT_LEFT_UP, wxCommandEventHandler( telepresenceFrame::RecvLeftKeyRelease ), NULL, this );
	
	m_button61->Connect( wxEVT_LEFT_DOWN, wxCommandEventHandler( telepresenceFrame::RecvRightKeyPress ), NULL, this );
	m_button61->Connect( wxEVT_LEFT_UP, wxCommandEventHandler( telepresenceFrame::RecvRightKeyRelease ), NULL, this );
	
	m_pCameraView->Connect(wxEVT_LEFT_DOWN, wxCommandEventHandler( telepresenceFrame::RecvRightKeyPressOnImage ), NULL, this );

	srand(time(NULL));

    update_timer_ = new wxTimer(this);
    update_timer_->Start(16);
    Connect(update_timer_->GetId(), wxEVT_TIMER, wxTimerEventHandler(telepresenceFrame::onUpdate), NULL, this);

    checkGoal_timer=new wxTimer(this);
    Connect(checkGoal_timer->GetId(), wxEVT_TIMER, wxTimerEventHandler(telepresenceFrame::checkGoalState), NULL, this);
    goalUp_timer=new wxTimer(this);
    Connect(goalUp_timer->GetId(), wxEVT_TIMER, wxTimerEventHandler(telepresenceFrame::sendGoalUp), NULL, this);
    goalDown_timer=new wxTimer(this);
    Connect(goalDown_timer->GetId(), wxEVT_TIMER, wxTimerEventHandler(telepresenceFrame::sendGoalDown), NULL, this);
    goalLeft_timer=new wxTimer(this);
    Connect(goalLeft_timer->GetId(), wxEVT_TIMER, wxTimerEventHandler(telepresenceFrame::sendGoalLeft), NULL, this);
    goalRight_timer=new wxTimer(this);
    Connect(goalRight_timer->GetId(), wxEVT_TIMER, wxTimerEventHandler(telepresenceFrame::sendGoalRight), NULL, this);
}

void telepresenceFrame::RecvRightKeyPressOnImage(wxCommandEvent& event)
{
mx = wxGetMousePosition().x - this->GetScreenPosition().x;
my = wxGetMousePosition().y - this->GetScreenPosition().y;
changed=true;
printf("x:%d, y:%d\n",mx,my);
//float columnaX = (mx - 320.0);
//float angle = asin((columnaX/320.0) * SINFOV);
//printf("angle:%f\n",angle);
////CvScalar s;
////s_mutex.Lock();
////wxCriticalSectionLocker lock(cs);
////s=cvGet2D(PointCloud_image,mx,my);
////s_mutex.Unlock();
//printf("s.val1:%f\n",s.val[0]);
//int aux;
//if (s.val[0]!=s.val[0])
//{
//printf("s.val[0]!=s.val[0]\n");
	//aux = 0;
//}
//else{
 //if (s.val[0]>5.12){ 
		//printf("s.val[0]>5.12\n");
		//aux = 255;
	//}else {
	//printf("else\n");
	//aux = (int)(s.val[0] * 1000) / 20;
	//}
//s.val[0] = aux;
//}
////cvSet2D(PointCloud_RGB_image,zz1,zz2,s);
//printf("s.val2:%f\n",s.val[0]);				
//float peopleZ = s.val[0] / 1000.0; // en metros
//float goalPositionX = cos(angle) * peopleZ;
//float goalPositionY = sin(angle) * peopleZ;
//printf("goalX:%f goalY:%f, z:%f\n",goalPositionX,goalPositionY,peopleZ);

}

void telepresenceFrame::imageDepth_callback(const sensor_msgs::ImageConstPtr& msg)
{
	//printf("kaixoooo\n");
	//wxMutexLocker lock(s_mutex);
	//wxCriticalSectionLocker lock(cs);
	if(changed)
	{
	changed=false;
	PointCloud_image = bridge.imgMsgToCv(msg, msg->encoding.c_str());
	try{
	s=cvGet2D(PointCloud_image,mx,my);
	}catch(cv::Exception& e)
	{
		printf("exception\n");
		printf("s.val[0] ex:%f\n",s.val[0]);
	}
	float columnaX = (mx - 320.0);
	float angle = asin((columnaX/320.0) * SINFOV);
	printf("angle:%f\n",angle);
	printf("s.val1:%f\n",s.val[0]);
	//int aux;
	//if (s.val[0]!=s.val[0])
	//{
	//printf("s.val[0]!=s.val[0]\n");
		//aux = 0;
	//}
	//else{
	 //if (s.val[0]>5.12){ 
			//printf("s.val[0]>5.12\n");
			//aux = 255;
		//}else {
		//printf("else\n");
		//aux = (int)(s.val[0] * 1000) / 20;
		//}
	//s.val[0] = aux;
	//}
	//printf("s.val2:%f\n",s.val[0]);				
	float peopleZ = s.val[0] / 1000.0; // en metros
	printf("peopleZ:%f\n",peopleZ);
	printf("data:%d, align:%d, width:%d, height:%d, depth:%d \n",PointCloud_image->imageData[200], PointCloud_image->align, PointCloud_image->width, PointCloud_image->height, PointCloud_image->depth);
	while(!ac->waitForServer(ros::Duration(5.0))){
	ROS_INFO("Waiting for the move_base action server to come up");
	}
	goal.target_pose.header.frame_id = "/base_link";
	goal.target_pose.pose.position.x = cos(angle) * peopleZ;
	goal.target_pose.pose.position.y = sin(angle) * peopleZ;
	printf("goalX:%d goalY:%d\n",goal.target_pose.pose.position.x,goal.target_pose.pose.position.y);
	goal.target_pose.pose.position.z=0;
	btQuaternion quat;
	quat.setRPY(0.0, 0.0, 0.0);
	tf::quaternionTFToMsg(quat,goal.target_pose.pose.orientation);
	goal.target_pose.header.stamp = ros::Time::now();
	ros::spinOnce();	
    if (ros::Time::now().toSec() - goal.target_pose.header.stamp.toSec() < 2)
    {
	   goal.target_pose.header.stamp = ros::Time::now();
	   ROS_INFO("Sending goal");

	   ac->sendGoal(goal);
	   checkGoal_timer->Start(500);
    }
    else
    {
		ROS_INFO("El objetivo es demasiado antiguo, no se intentará");
	}
	}
	
}
void telepresenceFrame::RecvDownKeyPress(wxCommandEvent& event)
{
	printf("down pressed\n");
	while(!ac->waitForServer(ros::Duration(5.0))){
	ROS_INFO("Waiting for the move_base action server to come up");
	}
	if(m_checkbox->GetValue()==true)
	{
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
	else
	{
		 goalDown_timer->Start(200);
	}
}

void telepresenceFrame::RecvDownKeyRelease(wxCommandEvent& event)
{
	printf("down released\n");
	goalDown_timer->Stop();
}

void telepresenceFrame::sendGoalUp(wxTimerEvent& evt)
{
	printf("sendGoalUp\n");
	vel.linear.x = 0.5; // m/s
	vel.linear.y = 0.0; // m/s
	vel.angular.z = 0.0; // rad/s
	vel_pub.publish(vel);
}

void telepresenceFrame::sendGoalDown(wxTimerEvent& evt)
{
	printf("sendGoalDown\n");
	vel.linear.x = -0.5; // m/s
	vel.linear.y = 0.0; // m/s
	vel.angular.z = 0.0; // rad/s
	vel_pub.publish(vel);
}

void telepresenceFrame::sendGoalRight(wxTimerEvent& evt)
{
	printf("sendGoalRight\n");
	vel.linear.x = 0.0; // m/s
	vel.linear.y = 0.0; // m/s
	vel.angular.z = 0.5; // rad/s
	vel_pub.publish(vel);
}

void telepresenceFrame::sendGoalLeft(wxTimerEvent& evt)
{
	printf("sendGoalLeft\n");
	vel.linear.x = 0.0; // m/s
	vel.linear.y = 0.0; // m/s
	vel.angular.z = -0.5; // rad/s
	vel_pub.publish(vel);
}

void telepresenceFrame::RecvUpKeyPress(wxCommandEvent& event)
{
	printf("left pressed");
	while(!ac->waitForServer(ros::Duration(5.0))){
	ROS_INFO("Waiting for the move_base action server to come up");
	}
	if(m_checkbox->GetValue()==true)
	{
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
	else
	{
		goalUp_timer->Start(200);
	}
}
void telepresenceFrame::RecvUpKeyRelease(wxCommandEvent& event)
{
	printf("left released\n");
	goalUp_timer->Stop();
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


void telepresenceFrame::RecvLeftKeyPress( wxCommandEvent& event )
{
	printf("RecvLeftKey");
	while(!ac->waitForServer(ros::Duration(5.0))){
	ROS_INFO("Waiting for the move_base action server to come up");
	}
	if(m_checkbox->GetValue()==true)
	{
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
	else
	{
		goalLeft_timer->Start(200);
	}
}

void telepresenceFrame::RecvLeftKeyRelease( wxCommandEvent& event )
{
	printf("left release\n");
	goalLeft_timer->Stop();
}
void telepresenceFrame::RecvRightKeyPress( wxCommandEvent& event )
{
	printf("RecvRightKey");
	while(!ac->waitForServer(ros::Duration(5.0))){
	ROS_INFO("Waiting for the move_base action server to come up");
	}
	if(m_checkbox->GetValue()==true)
	{
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
	else
	{
		goalRight_timer->Start(200);
	}		
}
void telepresenceFrame::RecvRightKeyRelease( wxCommandEvent& event )
{
	printf("right release\n");
	goalRight_timer->Stop();
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
	m_button56->Disconnect( wxEVT_LEFT_DOWN, wxCommandEventHandler( telepresenceFrame::RecvUpKeyPress ), NULL, this );
	m_button56->Disconnect( wxEVT_LEFT_UP, wxCommandEventHandler( telepresenceFrame::RecvUpKeyRelease ), NULL, this );

	m_button58->Disconnect( wxEVT_LEFT_DOWN, wxCommandEventHandler( telepresenceFrame::RecvDownKeyPress ), NULL, this );
	m_button58->Disconnect( wxEVT_LEFT_UP, wxCommandEventHandler( telepresenceFrame::RecvDownKeyRelease ), NULL, this );
	
	m_button57->Disconnect( wxEVT_LEFT_DOWN, wxCommandEventHandler( telepresenceFrame::RecvLeftKeyPress ), NULL, this );
	m_button57->Disconnect( wxEVT_LEFT_UP, wxCommandEventHandler( telepresenceFrame::RecvLeftKeyRelease ), NULL, this );
	
	m_button61->Disconnect( wxEVT_LEFT_DOWN, wxCommandEventHandler( telepresenceFrame::RecvRightKeyPress ), NULL, this );
	m_button61->Disconnect( wxEVT_LEFT_UP, wxCommandEventHandler( telepresenceFrame::RecvRightKeyRelease ), NULL, this );
	delete update_timer_;
	delete checkGoal_timer;
	delete goalUp_timer;
	delete goalDown_timer;
	delete goalRight_timer;
	delete goalLeft_timer;
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
