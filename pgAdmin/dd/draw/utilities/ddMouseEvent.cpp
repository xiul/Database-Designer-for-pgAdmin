//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawing.cpp - Container for figures that send changed events to Listeners whenever 
//	a part of its area was invalidated. Using the design pattern observer to decouple the
//	Drawing from its views and to enable multiple views .
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/utilities/ddMouseEvent.h"
#include "dd/draw/main/ddDrawingView.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


//This allow only to use selected functions from event and for conversion reason as main goal (unscrolled points)
ddMouseEvent::ddMouseEvent(wxMouseEvent& event, ddDrawingView *owner):
mouseEvent(event)
{  //mouseEvent is a private reference then should be initialize in constructor
	view=owner;
	m_shiftDown = event.m_shiftDown;
}

ddPoint& ddMouseEvent::GetPosition()
{
	return getUnScrolledPosition();
}

ddPoint& ddMouseEvent::getUnScrolledPosition()
{
	unScrolled = mouseEvent.GetPosition();
	view->CalcUnscrolledPosition(unScrolled.x,unScrolled.y,&unScrolled.x,&unScrolled.y);
	return unScrolled;
}

int ddMouseEvent::getUnScrolledPosX()
{
	return getUnScrolledPosition().x;
}

int ddMouseEvent::getUnScrolledPosY()
{
	return getUnScrolledPosition().y;
}

bool ddMouseEvent::LeftDClick()
{
	return mouseEvent.LeftDClick();
}

bool ddMouseEvent::ShiftDown()
{
	return mouseEvent.ShiftDown();
}

bool ddMouseEvent::RightDown()
{
	return mouseEvent.RightDown();
}

bool ddMouseEvent::LeftDown()
{
	return mouseEvent.LeftDown();
}

bool ddMouseEvent::LeftUp()
{
	return mouseEvent.LeftUp();
}

bool ddMouseEvent::LeftIsDown()
{
	return mouseEvent.LeftIsDown();
}

ddDrawingView* ddMouseEvent::getView()
{
	return view;
}