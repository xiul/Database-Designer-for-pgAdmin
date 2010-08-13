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

#ifndef DDBUTTONHANDLE_H
#define DDBUTTONHANDLE_H

#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/handles/ddLocatorHandle.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/utilities/ddPoint.h"

//class ddDrawingView;  //Hack-Fix to avoid circular reference
//class ddIFigure;

class ddButtonHandle : public ddIHandle
{
public:
	ddButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size);
    ~ddButtonHandle();

	virtual wxCursor createCursor();
	virtual ddRect& getDisplayBox();
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual ddPoint& locate();
	virtual void invokeStart(ddMouseEvent& event, ddDrawingView *view)=0;
	virtual void invokeStep(ddMouseEvent& event, ddDrawingView *view)=0;
	virtual void invokeEnd(ddMouseEvent& event, ddDrawingView *view)=0;
protected:
	wxBitmap buttonIcon;
private:
	bool clicked;
	ddILocator *bLocator;

};
#endif
