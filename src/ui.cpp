/*
 * Copyright (C) 2011, Oier Mees and Tekniker Technological Center 
 */
#include "tekniker_telepresence/ui.h"
#include <cstdlib>
#include <ctime>

namespace enc = sensor_msgs::image_encodings;

static const double pi = 3.14159265358979323846;

//define a new event and a callabck for our secondary thread which will do the image handling
DECLARE_EVENT_TYPE(wxEVT_COMMAND_MYTHREAD_UPDATE, -1)
DEFINE_EVENT_TYPE(wxEVT_COMMAND_MYTHREAD_UPDATE)
BEGIN_EVENT_TABLE(telepresenceFrame, wxFrame)
	EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_MYTHREAD_UPDATE, telepresenceFrame::OnThreadUpdate)
END_EVENT_TABLE()

int qw=0;

float vel_min=0.1;
float vel_max=0.4;
float vel_ang_min=0.15;
float vel_ang_max=0.7;
//UI constructor
telepresenceFrame::telepresenceFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 1100,700 ), wxDefaultSize );
	m_checkbox = new wxCheckBox(this, wxID_ANY, wxT("Navigation On?"), wxDefaultPosition, wxDefaultSize, 0);
	m_checkbox->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Joystick: OFF"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Acelerometer: OFF"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_pCameraView = new CCamView(this, wxPoint(5,15), wxSize(640, 480));
	m_pCameraView2 = new CCamView( this, wxPoint(0,0), wxSize(400, 300));
	ac = new MoveBaseClient("move_base", true);
	wxInitAllImageHandlers();
	m_bitmap = new wxStaticBitmap( this, wxID_ANY, wxBitmap( wxT("/opt/ros/diamondback/stacks/tekniker-ros-pkg/tekniker_telepresence/controller22.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	m_button56 = new wxButton( this, wxID_ANY, wxT("Forward"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button56->SetToolTip( wxT("Hold pressed to go forward") );
	m_button57 = new wxButton( this, wxID_ANY, wxT("Turn Left"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button57->SetToolTip( wxT("Hold pressed to turn left") );
	m_button61 = new wxButton( this, wxID_ANY, wxT("Turn Right"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button61->SetToolTip( wxT("Hold pressed to turn right") );
	m_button58 = new wxButton( this, wxID_ANY, wxT("Backward"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button58->SetToolTip( wxT("Hold pressed to go backward") );
	prgBar= new wxGauge(this,  wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL,  wxDefaultValidator, wxT("Battery"));
	prgBar->SetValue(70);
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Battery"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Webcam Status: OK"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Running in teleoperation mode!"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText7 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	//create a secondary thread for the image handling
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
	SetAutoLayout(TRUE);
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	bSizer4->Add( m_pCameraView, 0, wxALIGN_CENTER_HORIZONTAL, 0);
	wxBoxSizer* bSizer45;
	bSizer45 = new wxBoxSizer( wxVERTICAL );
	bSizer4->Add( bSizer45, 0,wxALIGN_RIGHT, 0);
	bSizer45->Add( m_pCameraView2, 0,wxALL, 5);
	bSizer1->Add( bSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxVERTICAL );
	bSizer32->Add( m_button56, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxHORIZONTAL );
	wxBoxSizer* bSizer35;
	bSizer35 = new wxBoxSizer( wxHORIZONTAL );
	bSizer35->Add( m_button57, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	bSizer38->Add( bSizer35, 1, wxEXPAND, 5 );
	bSizer38->Add( m_button61, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	bSizer37->Add( bSizer38, 1, wxEXPAND, 5 );
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	bSizer36->Add( m_button58, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	bSizer37->Add( bSizer36, 1, wxEXPAND, 5 );
	bSizer33->Add( bSizer37, 1, wxEXPAND, 5 );
	bSizer32->Add( bSizer33, 1, wxEXPAND, 5 );
	bSizer28->Add( bSizer32, 0, wxRIGHT|wxEXPAND|wxLEFT|wxDOWN, 10 );
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxVERTICAL );
	wxBoxSizer* bSizer41;
	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	bSizer39->Add( m_checkbox, 0, wxALL, 5 );
	bSizer39->Add(bSizer41);
	bSizer41->Add(bSizer42, 1, wxALL, 5);
	bSizer42->Add( m_staticText3, 0, wxALL, 5 );
	bSizer42->Add( m_staticText4, 0, wxALL, 5 );
	bSizer41->Add( m_bitmap, 0, wxALL|wxALIGN_TOP, 5 );
	bSizer45->Add( m_staticText2, 0, wxTOP|wxLEFT, 15 );
	bSizer45->AddSpacer(5);
	bSizer45->Add( prgBar, 0, wxLEFT, 15 );
	bSizer45->Add( m_staticText5, 0, wxTOP|wxLEFT, 15 );
	bSizer45->Add( m_staticText6, 0, wxTOP|wxLEFT, 15 );
	bSizer45->Add( m_staticText7, 0, wxTOP|wxLEFT, 15 );
	bSizer39->Add( bSizer40,0,wxEXPAND,5);
	bSizer28->Add( bSizer39, 1, wxEXPAND, 5 );
	bSizer1->Add( bSizer28, 0, wxEXPAND, 5 );
	this->SetSizer( bSizer1);
	this->Layout();

	changed=false;
	mx=0;
	my=0;
	linear_=1;
	angular_=2;
	safety_distance = 0;
	it_=new image_transport::ImageTransport(nh_);
	//read parameters from launcher file
	nh_.param("axis_linear", linear_, linear_);
	nh_.param("axis_angular", angular_, angular_);
	nh_.param("scale_angular", a_scale_, a_scale_);
	nh_.param("scale_linear", l_scale_, l_scale_);
	ros::param::get("safety_distance", safety_distance);
	image_pub_ = it_->advertise("/mywebcam", 1);
	image_color = it_->subscribe("/camera/rgb/image_color", 1, &telepresenceFrame::imageColor_callback, this);
	status = nh_.subscribe("segway_status", 1, &telepresenceFrame::status_callback, this);
	goal_pub = nh_.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);
	vel_pub = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 10);
	client = nh_.serviceClient<tekniker_kinect::depth_server>("get_kinect_depth");
	joy_sub_ = nh_.subscribe<joy::Joy>("joy", 10, &telepresenceFrame::joyCallback, this);
	ps3joy_activated=false;
	acelerometer_activated=false;
	
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
	
	m_checkbox->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( telepresenceFrame::checkBoxClicked ), NULL, this );

    // Connect timers
    update_timer_ = new wxTimer(this);
    update_timer_->Start(100);
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
//callback triggered after clicking on the image where the kinects video stream is shown
void telepresenceFrame::RecvRightKeyPressOnImage(wxCommandEvent& event)
{
	mx = wxGetMousePosition().x - this->GetScreenPosition().x - m_pCameraView->GetPosition().x-2;
	my = wxGetMousePosition().y - this->GetScreenPosition().y - m_pCameraView->GetPosition().y-27;
	printf("x:%d, y:%d\n",mx,my);
	tekniker_kinect::depth_server srv;
	srv.request.x = mx;
	srv.request.y = my;
	//call depth service to ask for the depth of (x,y) coordenates of the kinect
	//this way, we don't subscribe to the depth topic and save bandwidth
	if (client.call(srv))
	{
		ROS_INFO("Depth: %f", srv.response.depth);
	}
	else
	{
		ROS_ERROR("Failed to call service get_kinect_depth");
	}
	float columnaX = -1*(mx - 320.0);
	float angle = asin((columnaX/320.0) * SINFOV);
	printf("angle:%f\n",angle);
	goal.target_pose.header.frame_id = "/base_link";
	//if we don't substract safety_distance to the received depth, the robot goes to the exact
	//point of the obstacle that was clicked (for instance a person in the corridor)
	// and can't reach the destination because there is a obstacle on it
	//now, it should stop 0.5m before the obstacle
	if (safety_distance < srv.response.depth)
	{
		srv.response.depth -= safety_distance;
		printf("new depth :%f\n",srv.response.depth);
	}
	goal.target_pose.pose.position.x = cos(angle) * srv.response.depth;
	goal.target_pose.pose.position.y = sin(angle) * srv.response.depth;
	printf("goalX:%f goalY:%f\n",goal.target_pose.pose.position.x,goal.target_pose.pose.position.y);
	goal.target_pose.pose.position.z=0;
	btQuaternion quat;
	quat.setRPY(0.0, 0.0, 0.0);
	tf::quaternionTFToMsg(quat,goal.target_pose.pose.orientation);
	goal.target_pose.header.stamp = ros::Time::now();
	sendGoal();
}


void telepresenceFrame::checkBoxClicked(wxCommandEvent& event)
{
	if(m_checkbox->GetValue()==false && checkGoal_timer->IsRunning()==false)
	{
		m_staticText7->SetLabel(wxEmptyString);
		m_staticText6->SetLabel(wxT("Running in teleoperation mode!"));
		m_button56->SetToolTip( wxT("Hold pressed to go forward") );
		m_button57->SetToolTip( wxT("Hold pressed to turn left") );
		m_button61->SetToolTip( wxT("Hold pressed to turn right") );
		m_button58->SetToolTip( wxT("Hold pressed to go backward") );
	}
	if(m_checkbox->GetValue()==true && checkGoal_timer->IsRunning()==false)
	{
		m_staticText7->SetLabel(wxT("Navigation Status: None"));
		m_staticText6->SetLabel(wxT("Destination: None"));
		m_button56->SetToolTip( wxT("Click to navigate forward") );
		m_button57->SetToolTip( wxT("Click to navigate left") );
		m_button61->SetToolTip( wxT("Click to navigate right") );
		m_button58->SetToolTip( wxT("Click to navigate backward") );
	}

}
//check the robots battery. On our tests, the robot didn't publish any status info
//because of some driver issue
//TBD: Normalize the battery values in a scale and update battery proggress bar
void telepresenceFrame::status_callback(const segway_rmp::Status& msg)
{
	printf("pb:%d ui:%d\n", msg.pb_battery, msg.ui_battery);
}

void telepresenceFrame::RecvDownKeyPress(wxCommandEvent& event)
{
	printf("down pressed\n");
	if(m_checkbox->GetValue()==true)
	{
		waitForMoveBaseServer();
		btQuaternion quat;
	    quat.setRPY(0.0, 0.0, 0);
	    tf::quaternionTFToMsg(quat,goal.target_pose.pose.orientation);
	    goal.target_pose.header.stamp=ros::Time::now();
		goal.target_pose.header.frame_id = "/base_link";
		goal.target_pose.pose.position.x = -1;
	    goal.target_pose.pose.position.y = 0;
	    goal.target_pose.pose.position.z = 0;
		sendGoal();
	}
	else
	{
		if(checkGoal_timer->IsRunning()==false && (!ps3joy_activated && !acelerometer_activated))
		{
		 goalDown_timer->Start(200);
		}
	}
}
//in navigation mode, sends a goal to the robot
void telepresenceFrame::sendGoal()
{
		if (ros::Time::now().toSec() - goal.target_pose.header.stamp.toSec() < 2)
	   {
		   goal.target_pose.header.stamp = ros::Time::now();
		   ROS_INFO("Sending goal");
		   m_staticText7->SetLabel(wxT("Navigation Status: Sending goal"));
		   wxString mystring = wxString::Format(wxT("Destination: %f, %f orientation: %f"), goal.target_pose.pose.position.x, goal.target_pose.pose.position.y, goal.target_pose.pose.orientation.z);
		   m_staticText6->SetLabel(mystring);
		   ac->sendGoal(goal);
		   checkGoal_timer->Start(500);
	   }
	   else
		   ROS_INFO("The destination is too old, aborting");
		   m_staticText7->SetLabel(wxT("Navigation Status: The destination is too old, aborting"));
}
//check the sent goals state and update the UI with the feedback
void telepresenceFrame::checkGoalState(wxTimerEvent& evt)
{
	actionlib::SimpleClientGoalState aux=ac->getState();
	if(aux!=actionlib::SimpleClientGoalState::PENDING && aux!=actionlib::SimpleClientGoalState::ACTIVE)
	{
		if(aux == actionlib::SimpleClientGoalState::SUCCEEDED)
		{
			ROS_INFO("Destination reached successfully");
			m_staticText7->SetLabel(wxT("Navigation Status: Destination reached successfully"));
		}
        else
        {
            ROS_INFO("Couldn't reach destination");
    		m_staticText7->SetLabel(wxT("Navigation Status: Couldn't reach destination"));
		}
        checkGoal_timer->Stop();
	}
	else
	{
		ROS_INFO("pending or active ");
		m_staticText7->SetLabel(wxT("Navigation Status: pending or active..."));
	}
}

void telepresenceFrame::RecvDownKeyRelease(wxCommandEvent& event)
{
	printf("down released\n");
	goalDown_timer->Stop();
}

//send velocity commands directly to the motor when in teleoperation mode
void telepresenceFrame::sendGoalUp(wxTimerEvent& evt)
{
	printf("sendGoalUp\n");
	vel.linear.x = 0.5; // m/s
	vel.linear.y = 0.0; // m/s
	vel.angular.z = 0.0; // rad/s
	vel_pub.publish(vel);
}
//send velocity commands directly to the motor when in teleoperation mode
void telepresenceFrame::sendGoalDown(wxTimerEvent& evt)
{
	printf("sendGoalDown\n");
	vel.linear.x = -0.5; // m/s
	vel.linear.y = 0.0; // m/s
	vel.angular.z = 0.0; // rad/s
	vel_pub.publish(vel);
}
//send velocity commands directly to the motor when in teleoperation mode
void telepresenceFrame::sendGoalRight(wxTimerEvent& evt)
{
	printf("sendGoalRight\n");
	vel.linear.x = 0.0; // m/s
	vel.linear.y = 0.0; // m/s
	vel.angular.z = -0.5; // rad/s
	vel_pub.publish(vel);
}

//send velocity commands directly to the motor when in teleoperation mode
void telepresenceFrame::sendGoalLeft(wxTimerEvent& evt)
{
	printf("sendGoalLeft\n");
	vel.linear.x = 0.0; // m/s
	vel.linear.y = 0.0; // m/s
	vel.angular.z = 0.5; // rad/s
	vel_pub.publish(vel);
}
//FIXME: The UI freezes while it's waiting for the movebase server to 
//come up
void telepresenceFrame::waitForMoveBaseServer()
{
		while(!ac->waitForServer(ros::Duration(3.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
		m_staticText7->SetLabel(wxT("Navigation Status: Waiting for the move_base action server to come up"));
		}
}
void telepresenceFrame::RecvUpKeyPress(wxCommandEvent& event)
{
	printf("up pressed\n");
	if(m_checkbox->GetValue()==true && checkGoal_timer->IsRunning()==false)
	{
		waitForMoveBaseServer();
		btQuaternion quat;
		quat.setRPY(0.0, 0.0, 0);
		tf::quaternionTFToMsg(quat,goal.target_pose.pose.orientation);
		goal.target_pose.header.stamp=ros::Time::now();
		goal.target_pose.header.frame_id = "/base_link";
		goal.target_pose.pose.position.x = 1;
		goal.target_pose.pose.position.y = 0;
		goal.target_pose.pose.position.z = 0;
		sendGoal();
	}
	else
	{
		if (checkGoal_timer->IsRunning()==false && (!ps3joy_activated && !acelerometer_activated))
		{
		goalUp_timer->Start(200);
		}
	}
}
void telepresenceFrame::RecvUpKeyRelease(wxCommandEvent& event)
{
	printf("up released\n");
	goalUp_timer->Stop();
}


void telepresenceFrame::RecvLeftKeyPress( wxCommandEvent& event )
{
	printf("left pressed\n");
	if(m_checkbox->GetValue()==true && checkGoal_timer->IsRunning()==false)
	{
		waitForMoveBaseServer();
		btQuaternion quat;
	    quat.setRPY(0.0, 0.0, pi/2);
	    tf::quaternionTFToMsg(quat,goal.target_pose.pose.orientation);
	    goal.target_pose.header.stamp=ros::Time::now();
		goal.target_pose.header.frame_id = "/base_link";
		goal.target_pose.pose.position.x = 0;
	    goal.target_pose.pose.position.y = 0;
	    goal.target_pose.pose.position.z = 0;
		sendGoal();
	}
	else
	{
		if (checkGoal_timer->IsRunning()==false && (!ps3joy_activated && !acelerometer_activated))
		{
		goalLeft_timer->Start(200);
		}
	}
}

void telepresenceFrame::RecvLeftKeyRelease( wxCommandEvent& event )
{
	printf("left release\n");
	goalLeft_timer->Stop();
}
void telepresenceFrame::RecvRightKeyPress( wxCommandEvent& event )
{
	printf("right pressed\n");
	if(m_checkbox->GetValue()==true && checkGoal_timer->IsRunning()==false)
	{
		waitForMoveBaseServer();
		btQuaternion quat;
	    quat.setRPY(0.0, 0.0, -pi/2);
	    tf::quaternionTFToMsg(quat,goal.target_pose.pose.orientation);
	
	    goal.target_pose.header.stamp=ros::Time::now();
		goal.target_pose.header.frame_id = "/base_link";
		goal.target_pose.pose.position.x = 0;
	    goal.target_pose.pose.position.y = 0;
	    goal.target_pose.pose.position.z = 0;
		sendGoal();
	}
	else
	{
		if (checkGoal_timer->IsRunning()==false && (!ps3joy_activated && !acelerometer_activated))
		{
		goalRight_timer->Start(200);
		}
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

//draw the webcams video stream on the UI
void telepresenceFrame::OnThreadUpdate(wxCommandEvent& evt)
{

	m_pCameraView2->DrawCam(_IplImg2);
	cv::Mat aux(_IplImg2);
	cv_bridge::CvImage cv_ptr2;
	cv_ptr2.encoding=sensor_msgs::image_encodings::RGB8;
	cv_ptr2.image=aux;

	image_pub_.publish(cv_ptr2.toImageMsg());
}
//receive the kinects video stream and show it on the UI
void telepresenceFrame::imageColor_callback(const sensor_msgs::ImageConstPtr& msg)
{
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
	_IplImg=cv_ptr->image;
	m_pCameraView->DrawCam(&_IplImg);

}
//worker thread for image handling
 wxThread::ExitCode telepresenceFrame::Entry()
        {
            CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
            cvSetCaptureProperty(capture,CV_CAP_PROP_CONVERT_RGB, false);
            //check for the webcam, if cvCaptureFromCAM doesn't work with any index
            //try enabling the v4l and ffmpg flags in opencv2 Makefile and compiling it again
            //(rosmake opencv2) you may have to delete the ROS_NOBUILD
			if ( !capture )
			{
				fprintf( stderr, "ERROR: webcam capture is NULL \n" );
			}
            while (!GetThread()->TestDestroy())
            {
				IplImage *aux=cvQueryFrame( capture );
				_IplImg2=aux;
				cvConvertImage(aux,_IplImg2,CV_CVTIMG_SWAP_RB);
				//we grabed a new image from the webcam so fire up our event
				//and call onThreadUpdate to draw it
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
            printf("2.thread will be exited\n");
            return (wxThread::ExitCode)0;
        }

//in teleoperation mode, send velocity commands to the robots motor using PS3 controller joystick
// see http://www.ros.org/wiki/ps3joy/Tutorials/PairingJoystickAndBluetoothDongle
void telepresenceFrame::sendJoystickVel(double joystick_vel, double joystick_ang)
{
	vel.linear.y = 0.0; // m/s
	if(joystick_vel>0)
	{
		if(joystick_vel<vel_min)
		{
			vel.linear.x=vel_min;
			//ROS_INFO("joystick_vel>0 && joystick_vel<vel_min");
		}
		if (joystick_vel>vel_min)
		{
		vel.linear.x=vel_max*(joystick_vel/2);
		//ROS_INFO("joystick_vel>vel_min");
		}
	}
	else if(joystick_vel==0)
	{
		vel.linear.x=0;
		//ROS_INFO("joystick_vel==0");
	}
	else if(joystick_vel<0)
	{
		if(joystick_vel>(-1)*vel_min)
		{
			vel.linear.x=vel_min;
			//ROS_INFO("joystick_vel<0 && (joystick_vel>(-1)*vel_min)");
		}
		if(joystick_vel<(-1)*vel_min)
		{
			vel.linear.x=vel_max*(joystick_vel/2);
			//ROS_INFO("joystick_vel<0 && (joystick_vel<(-1)*vel_min)");
		}
	}
	
	
	if(joystick_ang>0)
	{
		if(joystick_ang<vel_ang_min)
		{
			vel.angular.z=vel_ang_min;
			//ROS_INFO("joystick_ang>0 && joystick_ang<vel_ang_min");
		}

		if (joystick_ang>vel_ang_min)
		{
		vel.angular.z=vel_ang_max*(joystick_ang/2);
		//ROS_INFO("joystick_ang>vel_ang_min");
		}
	} 
	else if (joystick_ang==0)
	{
		vel.angular.z=0;
		//ROS_INFO("joystick_ang==0");
	}
	else if (joystick_ang<0)
	{
		if(joystick_ang>(-1)*vel_ang_min)
		{
			vel.angular.z=vel_ang_min;
			//ROS_INFO("joystick_ang<0 && (joystick_ang>(-1)*vel_ang_min)");
		}
		if(joystick_ang<(-1)*vel_ang_min)
		{
			vel.angular.z=vel_ang_max*(joystick_ang/2);
			//ROS_INFO("joystick_ang<0 && (joystick_ang<(-1)*vel_ang_min)");
		}
	}

	vel_pub.publish(vel);
	ROS_INFO("joystick angular %f, lineal %f",joystick_ang, joystick_vel);
	ROS_INFO("sending angular %f, lineal %f",vel.angular.z, vel.linear.x);

}
//display the controller mode on the UI
void telepresenceFrame::changeLabel(int buttonNumber, bool var)
{
			if(buttonNumber==15)
			{
				if(var==true)
				{
					m_staticText3->SetLabel(wxT("Joystick: ON"));	
				}
				else
				{
					m_staticText3->SetLabel(wxT("Joystick: OFF"));	
				}		
			}else if(buttonNumber==12)
			{
				if(var==true)
				{
					m_staticText4->SetLabel(wxT("Acelerometer: ON"));			
				}
				else
				{
					m_staticText4->SetLabel(wxT("Acelerometer: OFF"));
				}			
			}
}
//this is necessary because somehow the controller is very unreliable at detecting when you press a button
//it often detects more than one presses, so we count the time between presses to determine if it is a valid press
void telepresenceFrame::timeOnButtonPress(bool &boolean_var,bool &boolean_var2, int buttonNumber, const joy::Joy::ConstPtr& joy)
{
	if (boolean_var==false && joy->buttons[buttonNumber]==1)
	{
		if(qw==0)// first time
		{
			begin = ros::Time::now();
			boolean_var=true;
			qw++;
			changeLabel(buttonNumber, true);
		}
		else
		{
			end2 = ros::Time::now();
			ros::Duration e=end2-begin2;
			if(e.toSec()>2.0 && boolean_var2==false)
			{
				boolean_var=true;
				begin = ros::Time::now();
				changeLabel(buttonNumber, true); 
			}

		}
	}
	else if(boolean_var==true && joy->buttons[buttonNumber]==1)
	{
		end = ros::Time::now();
		ros::Duration d=end-begin;
		if(d.toSec()>2.0)
		{
			boolean_var=false;
			begin2 = ros::Time::now();
			changeLabel(buttonNumber, false);
		}
	}
}
//PS3 Controller callback
void telepresenceFrame::joyCallback(const joy::Joy::ConstPtr& joy)
{
	double joystick_ang=a_scale_*joy->axes[angular_];
	double joystick_vel=l_scale_*joy->axes[linear_];
	timeOnButtonPress(ps3joy_activated, acelerometer_activated, 15, joy);
	timeOnButtonPress(acelerometer_activated, ps3joy_activated, 12, joy);
	if(acelerometer_activated==true && ps3joy_activated==false)//activate to use acelerometer
	{
		ROS_INFO("Right-Left:%f Forward-Backward:%f",joy->axes[16], joy->axes[17]);
		sendJoystickVel(20*joy->axes[17], -20*joy->axes[16]);
	}
	if(acelerometer_activated==false && ps3joy_activated==true)
	{
		sendJoystickVel(joystick_vel, joystick_ang);
	}
}
//destructor
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
	delete goalUp_timer;
	delete goalDown_timer;
	delete goalRight_timer;
	delete goalLeft_timer;
	delete m_pCameraView;
	delete m_pCameraView2;
	delete prgBar;
	delete m_bitmap;
	delete m_button56;
	delete m_button57;
	delete m_button61;
	delete m_button58;
	delete m_staticText2;
	delete m_checkbox;
	delete m_staticText3;
	delete m_staticText4;
	delete m_staticText5;
	delete m_staticText6;
	delete m_staticText7;
	delete ac;
	delete PointCloud_image;
	if(it_!=NULL)
		delete it_;
	if (GetThread() && GetThread()->IsRunning())
	{
		printf("deleta thread\n");
		GetThread()->Delete();
	}
}
