/*
 * Copyright (C) 2010, Oier Mees and Technological Center Tekniker
 */

#include <wx/wx.h>
#include <wx/app.h>
#include "tekniker_telepresence/ui.h"
#include <ros/ros.h>



class MainApp : public wxApp
{
public:
  char** _argvForRos;
  ros::NodeHandlePtr _nodeHandlePtr;
  
  bool OnInit() {
	  
    InitializeRos();
    CreateMainWindow();

    return true;
  }

  int OnExit() {
    for (int i = 0; i < argc; ++i) {
      free(_argvForRos[i]);
    }

    delete [] _argvForRos;

    return 0;
  }

  void InitializeRos() {
    // create our own copy of argv, with regular char*s.
    _argvForRos =  new char*[argc];

    for (int i = 0; i < argc; ++i) {
      _argvForRos[i] = strdup( wxString( argv[i] ).mb_str() );
    }

    ros::init(argc, _argvForRos, "kinecta");
    _nodeHandlePtr.reset(new ros::NodeHandle);
  }


  void CreateMainWindow() {
    telepresenceFrame * frame = new telepresenceFrame(NULL);


    frame->Show();
    SetTopWindow(frame);
  }
};
DECLARE_APP(MainApp);
IMPLEMENT_APP(MainApp);
