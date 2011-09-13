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
int qw=0;
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
	controller_checkbox = new wxCheckBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	controller_checkbox->SetValue(false);
	controller_checkbox->Disable();
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("PS3 controller activated?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
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
	m_staticText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	
	bSizer39->Add( m_checkbox, 0, wxALL, 5 );
	bSizer39->Add( controller_checkbox, 0, wxLEFT|wxTOP|wxBOTTOM, 5 );
	bSizer39->Add( m_staticText3, 0, wxRIGHT|wxTOP|wxBOTTOM, 8 );
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

	linear_=1;
	angular_=2;
	it_=new image_transport::ImageTransport(nh_);
	nh_.param("axis_linear", linear_, linear_);
	nh_.param("axis_angular", angular_, angular_);
	nh_.param("scale_angular", a_scale_, a_scale_);
	nh_.param("scale_linear", l_scale_, l_scale_);
	//image_pub_ = it_->advertise("out", 1);
	image_pub_ = it_->advertise("/mywebcam", 1);
	image_color = it_->subscribe("/camera/rgb/image_color", 1, &telepresenceFrame::imageColor_callback, this);
	status = nh_.subscribe("segway_status", 1, &telepresenceFrame::status_callback, this);
	goal_pub = nh_.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal", 1);
	vel_pub = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 10);
	client = nh_.serviceClient<tekniker_kinect::depth_server>("get_kinect_depth");
	joy_sub_ = nh_.subscribe<joy::Joy>("joy", 10, &telepresenceFrame::joyCallback, this);
	ps3joy_activated=false;
	
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
    update_timer_->Start(100);
    Connect(update_timer_->GetId(), wxEVT_TIMER, wxTimerEventHandler(telepresenceFrame::onUpdate), NULL, this);

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
	//printf("x1:%d y1:%d\n",this->GetScreenPosition().x,this->GetScreenPosition().y);
	//printf("xx:%d yy:%d\n",wxGetMousePosition().x,wxGetMousePosition().y);
	//printf("xxx:%d yyy:%d\n",m_pCameraView->GetPosition().x, m_pCameraView->GetPosition().y);
	mx = wxGetMousePosition().x - this->GetScreenPosition().x - m_pCameraView->GetPosition().x-2;
	my = wxGetMousePosition().y - this->GetScreenPosition().y - m_pCameraView->GetPosition().y-27;
	printf("x:%d, y:%d\n",mx,my);
	tekniker_kinect::depth_server srv;
	srv.request.x = mx;
	srv.request.y = my;
	if (client.call(srv))
	{
		ROS_INFO("Depth: %ld", (long int)srv.response.depth);
	}
	else
	{
		ROS_ERROR("Failed to call service get_kinect_depth");
	}
	float columnaX = -1*(mx - 320.0);
	float angle = asin((columnaX/320.0) * SINFOV);
	printf("angle:%f\n",angle);
	printf("peopleZ:%f\n",srv.response.depth);
	goal.header.frame_id = "/base_link";
	goal.pose.position.x = cos(angle) * srv.response.depth;
	goal.pose.position.y = sin(angle) * srv.response.depth;
	printf("goalX:%f goalY:%f\n",goal.pose.position.x,goal.pose.position.y);
	goal.pose.position.z=0;
	btQuaternion quat;
	quat.setRPY(0.0, 0.0, 0.0);
	tf::quaternionTFToMsg(quat,goal.pose.orientation);
	goal.header.stamp = ros::Time::now();
	goal_pub.publish(goal);
}



void telepresenceFrame::status_callback(const segway_rmp::Status& msg)
{
	printf("pb:%d ui:%d\n", msg.pb_battery, msg.ui_battery);
}

void telepresenceFrame::RecvDownKeyPress(wxCommandEvent& event)
{
	printf("down pressed\n");
	if(m_checkbox->GetValue()==true)
	{
		btQuaternion quat;
	    quat.setRPY(0.0, 0.0, 0);
	    tf::quaternionTFToMsg(quat,goal.pose.orientation);
	    goal.header.stamp=ros::Time::now();
		goal.header.frame_id = "/base_link";
		goal.pose.position.x = -1;
	    goal.pose.position.y = 0;
	    goal.pose.position.z = 0;
		goal_pub.publish(goal);
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
	vel.angular.z = -0.5; // rad/s
	vel_pub.publish(vel);
}

void telepresenceFrame::sendGoalLeft(wxTimerEvent& evt)
{
	printf("sendGoalLeft\n");
	vel.linear.x = 0.0; // m/s
	vel.linear.y = 0.0; // m/s
	vel.angular.z = 0.5; // rad/s
	vel_pub.publish(vel);
}

void telepresenceFrame::RecvUpKeyPress(wxCommandEvent& event)
{
	printf("up pressed\n");
	if(m_checkbox->GetValue()==true)
	{
		btQuaternion quat;
		quat.setRPY(0.0, 0.0, 0);
		tf::quaternionTFToMsg(quat,goal.pose.orientation);
		goal.header.stamp=ros::Time::now();
		goal.header.frame_id = "/base_link";
		goal.pose.position.x = 1;
		goal.pose.position.y = 0;
		goal.pose.position.z = 0;
		goal_pub.publish(goal);
	}
	else
	{
		goalUp_timer->Start(200);
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
	if(m_checkbox->GetValue()==true)
	{
		btQuaternion quat;
	    quat.setRPY(0.0, 0.0, pi/2);
	    tf::quaternionTFToMsg(quat,goal.pose.orientation);
	    goal.header.stamp=ros::Time::now();
		goal.header.frame_id = "/base_link";
		goal.pose.position.x = 0;
	    goal.pose.position.y = 0;
	    goal.pose.position.z = 0;
		goal_pub.publish(goal);
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
	printf("right pressed\n");
	if(m_checkbox->GetValue()==true)
	{
		btQuaternion quat;
	    quat.setRPY(0.0, 0.0, -pi/2);
	    tf::quaternionTFToMsg(quat,goal.pose.orientation);
	
	    goal.header.stamp=ros::Time::now();
		goal.header.frame_id = "/base_link";
		goal.pose.position.x = 0;
	    goal.pose.position.y = 0;
	    goal.pose.position.z = 0;
		goal_pub.publish(goal);
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
	_IplImg=cv_ptr->image;
	m_pCameraView->DrawCam(&_IplImg);

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

				IplImage *aux=cvQueryFrame( capture );
				_IplImg2=aux;
				cvConvertImage(aux,_IplImg2,CV_CVTIMG_SWAP_RB);
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

void telepresenceFrame::joyCallback(const joy::Joy::ConstPtr& joy)
{
	vel.linear.y = 0.0; // m/s
	float vel_min=0.1;
	float vel_max=0.4;
	float vel_ang_min=0.15;
	float vel_ang_max=0.7;
	double joystick_ang=a_scale_*joy->axes[angular_];
	double joystick_vel=l_scale_*joy->axes[linear_];
	if(ps3joy_activated==false && joy->buttons[15]==1)
	{
		if(qw==0)// first time
		{
			begin = ros::Time::now();
			ROS_INFO("begin %f",begin.toSec());
			ROS_INFO("PS3 controller activated! begin");
			ps3joy_activated=true;
			qw++;
			controller_checkbox->SetValue(true);
		}
		else
		{
			end2 = ros::Time::now();
			ROS_INFO("end2 %f",end2.toSec());
			ros::Duration e=end2-begin2;
			ROS_INFO("kenketa2: %f",e.toSec());
			if(e.toSec()>2.0)
			{
				ps3joy_activated=true;
				ROS_INFO("PS3 controller activated!");
				begin = ros::Time::now();
				controller_checkbox->SetValue(true);
			}
		}
	}
	else if(ps3joy_activated==true && joy->buttons[15]==1)
	{
		end = ros::Time::now();
		ROS_INFO("end %f",end.toSec());
		ros::Duration d=end-begin;
		ROS_INFO("kenketa: %f",d.toSec());
		if(d.toSec()>2.0)
		{
		ps3joy_activated=false;
		ROS_INFO("PS3 controller desactivated!");
		begin2 = ros::Time::now();
		controller_checkbox->SetValue(false);
		}
	}
	if (ps3joy_activated==true)
	{
		if(joystick_vel>0)
		{
			if(joystick_vel<vel_min)
			{
				vel.linear.x=vel_min;
				ROS_INFO("joystick_vel>0 && joystick_vel<vel_min");
			}
			if (joystick_vel>vel_min)
			{
			vel.linear.x=vel_max*(joystick_vel/2);
			ROS_INFO("joystick_vel>vel_min");
			}
		}
		else if(joystick_vel==0)
		{
			vel.linear.x=0;
			ROS_INFO("joystick_vel==0");
		}
		else if(joystick_vel<0)
		{
			if(joystick_vel>(-1)*vel_min)
			{
				vel.linear.x=vel_min;
				ROS_INFO("joystick_vel<0 && (joystick_vel>(-1)*vel_min)");
			}
			if(joystick_vel<(-1)*vel_min)
			{
				vel.linear.x=vel_max*(joystick_vel/2);
				ROS_INFO("joystick_vel<0 && (joystick_vel<(-1)*vel_min)");
			}
		}
		
		
		if(joystick_ang>0)
		{
			if(joystick_ang<vel_ang_min)
			{
				vel.angular.z=vel_ang_min;
				ROS_INFO("joystick_ang>0 && joystick_ang<vel_ang_min");
			}
	
			if (joystick_ang>vel_ang_min)
			{
			vel.angular.z=vel_ang_max*(joystick_ang/2);
			ROS_INFO("joystick_ang>vel_ang_min");
			}
		} 
		else if (joystick_ang==0)
		{
			vel.angular.z=0;
			ROS_INFO("joystick_ang==0");
		}
		else if (joystick_ang<0)
		{
			if(joystick_ang>(-1)*vel_ang_min)
			{
				vel.angular.z=vel_ang_min;
				ROS_INFO("joystick_ang<0 && (joystick_ang>(-1)*vel_ang_min)");
			}
			if(joystick_ang<(-1)*vel_ang_min)
			{
				vel.angular.z=vel_ang_max*(joystick_ang/2);
				ROS_INFO("joystick_ang<0 && (joystick_ang<(-1)*vel_ang_min)");
			}
		}

		vel_pub.publish(vel);
		ROS_INFO("joystick angular %f, lineal %f",joystick_ang, joystick_vel);
		ROS_INFO("sending angular %f, lineal %f",vel.angular.z, vel.linear.x);
	}
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
	delete goalUp_timer;
	delete goalDown_timer;
	delete goalRight_timer;
	delete goalLeft_timer;
	delete &goal;
	delete m_pCameraView;
	delete m_pCameraView2;
	if(it_!=NULL)
		delete it_;
	if (GetThread() && GetThread()->IsRunning())
	{
		printf("deleta thread\n");
		GetThread()->Delete();
	}
}
