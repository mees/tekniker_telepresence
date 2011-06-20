////////////////////////////////////////////////////////////////////
// Package:		worker definition
// File:		worker.h
// Purpose:		manage checking, switching tasks
//
// Created by:	Larry Lart on 06-Jul-2006
// Updated by:
//
////////////////////////////////////////////////////////////////////

#ifndef _WORKER_H
#define _WORKER_H

#include "wx/wxprec.h"
#include "wx/thread.h"
#include "tekniker_telepresence/camview.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers


//////////////////////////////////////////////////
// class:	CX10PingWorker
/////////////////////////////////////////////////
class CwxopencvWorker : public wxThread
{
// methods
public:
	CwxopencvWorker(CCamView *pFrame );
	~CwxopencvWorker( );

	// thread entry point
	virtual void *Entry();
	virtual void OnExit();
	double GetTime( void );

// data
public:
    	CCamView		*m_pFrame;
	

	// timers
	double m_nCpuFreq;
	unsigned char	m_bLife;

// private data
private:
	// process syncronizer/locker
	wxMutex *m_pMutex;

};

#endif


