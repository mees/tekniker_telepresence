////////////////////////////////////////////////////////////////////
// Name:		implementation of the CCamView class
// File:		camview.cpp
// Purpose:		eye/camera view/GUI system control methods
//
// Created by:	Larry Lart on 22-Feb-2006
// Updated by:	
//
// Copyright:	(c) 2006 Larry Lart
////////////////////////////////////////////////////////////////////

// system header
#include <math.h>
#include <stdio.h>
#include "highgui.h"
#include "cv.h"
#include "cvaux.h"

#ifdef __GNUG__
#pragma implementation
#pragma interface
#endif

#include "wx/wxprec.h"
#include <wx/image.h>

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers


// main header
#include "tekniker_telepresence/camview.h"

// implement message map
BEGIN_EVENT_TABLE(CCamView, wxWindow)
	EVT_PAINT( CCamView::OnPaint )
	EVT_SIZE( CCamView::OnSize ) 
END_EVENT_TABLE()

////////////////////////////////////////////////////////////////////
// Method:	Constructor
// Class:	CCamView
// Purose:	build my CCamView object
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
CCamView::CCamView( wxWindow *frame, const wxPoint& pos, const wxSize& size ):
			wxWindow(frame, -1, pos, size, wxSIMPLE_BORDER )
{
	

	// set my canvas width/height
	m_nWidth = size.GetWidth( );
	m_nHeight = size.GetHeight( );

	m_bDrawing = false;

	m_bNewImage = 0;
}

////////////////////////////////////////////////////////////////////
// Method:	Destructor
// Class:	CCamView
// Purose:	destroy my object
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
CCamView::~CCamView( )
{
	
}



////////////////////////////////////////////////////////////////////
// Method:	OnPaint
// Class:	CCamView
// Purose:	on paint event
// Input:	reference to paint event
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamView::OnPaint( wxPaintEvent& event )
{
	wxPaintDC dc(this);
	Draw( dc );
}

////////////////////////////////////////////////////////////////////
// Method:	Draw
// Class:	CCamView
// Purose:	camera drawing
// Input:	reference to dc
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamView::Draw( wxDC& dc )
{
	// check if dc available
	if( !dc.Ok( ) || m_bDrawing == true ){ return; }

		m_bDrawing = true;

		dc.BeginDrawing();

		int x,y,w,h;
		dc.GetClippingBox( &x, &y, &w, &h );
		// if there is a new image to draw
		if( m_bNewImage )
		{
			dc.DrawBitmap( m_pBitmap, x, y );
			m_bNewImage = false;
		} else
		{
			// draw inter frame ?
		}

		dc.EndDrawing();
		m_bDrawing = false;

	return;
}

////////////////////////////////////////////////////////////////////
// Method:	OnDraw
// Class:	CCamView
// Purose:	CCamView drawing
// Input:	nothing
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamView::DrawCam( IplImage* pImg )
{

	if( m_bDrawing ) return;
	m_bDrawing = true;

	// if there was an image then we need to update view
    if( pImg )
    {
        IplImage* pDstImg = cvCloneImage( pImg ); 
		int nCamWidth = pImg->width;
		int nCamHeight =pImg->height;
		//printf("drawcam m_nWidth:%d m_nHeight:%d\n",m_nWidth, m_nHeight);

		// draw a rectangle
		//cvRectangle( pDstImg,
					//cvPoint( 10, 10 ),
					//cvPoint( nCamWidth-10, nCamHeight-10 ),
					//CV_RGB( 0,255,0 ), 1 );


		// process image from opencv to wxwidgets
		unsigned char *rawData;
		// draw my stuff to output canvas
		CvSize roiSize;
		int step = 0;
		// get raw data from ipl image
		cvGetRawData( pDstImg, &rawData, &step, &roiSize );
		// convert data from raw image to wxImg 
		wxImage pWxImg = wxImage( nCamWidth, nCamHeight, rawData, TRUE );
		// convert to bitmap to be used by the window to draw
		//m_pBitmap = wxBitmap( pWxImg.Scale(m_nWidth, m_nHeight) );
		m_pBitmap = wxBitmap( pWxImg );
		m_bNewImage = true;
		m_bDrawing = false;

		Refresh( FALSE );

		Update( );

		cvReleaseImage( &pDstImg );

    }

}

////////////////////////////////////////////////////////////////////
// Method:	CheckUpdate
// Class:	CCamView
// Purose:	CHeck for updates
// Input:	reference to size event
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamView::CheckUpdate()
{
	Update( );
}

////////////////////////////////////////////////////////////////////
// Method:	OnSize
// Class:	CCamView
// Purose:	adjust on windows resize
// Input:	reference to size event
// Output:	nothing
////////////////////////////////////////////////////////////////////
void CCamView::OnSize( wxSizeEvent& even )
{
	int nWidth = even.GetSize().GetWidth();
	int nHeight = even.GetSize().GetHeight();

	m_nWidth = nWidth;
	m_nHeight = nHeight;
	printf("on size, m_nWidth:%d  m_nHeight:%d\n",m_nWidth,m_nHeight);

}
