//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbObject.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbObject.h - 
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDMOUSEEVENT_H
#define DDMOUSEEVENT_H
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/main/ddObject.h"

class ddDrawingView;	//FIX-HACK for circular reference



//DD-TODO: in a future this should be customized event???
class ddMouseEvent : public ddObject
{
	public:
		ddMouseEvent(wxMouseEvent& event, ddDrawingView *owner);
		ddPoint& getUnScrolledPosition();
		ddPoint& GetPosition();
		int getUnScrolledPosX();
		int getUnScrolledPosY();
		bool LeftDClick();
		bool LeftDown();
		bool LeftIsDown();
		bool LeftUp();
		bool ShiftDown();
		bool RightDown();
		bool m_shiftDown;
		ddDrawingView* getView();
private:
		ddDrawingView *view;
		wxMouseEvent& mouseEvent;
		ddPoint unScrolled;
};
#endif
