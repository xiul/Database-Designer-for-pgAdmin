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

#ifndef DDPOLYLINEHANDLE
#define DDPOLYLINEHANDLE

#include "dd/draw/handles/ddLocatorHandle.h"
#include "dd/draw/utilities/ddRect.h"

class ddDrawingView;  //Hack-Fix to avoid circular reference
class ddPolyLineFigure;

class ddPolyLineHandle : public ddLocatorHandle
{
public:
	ddPolyLineHandle(ddPolyLineFigure *figure, ddILocator *loc, int index);
    ~ddPolyLineHandle();

	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	//virtual ddPoint* locate();
	virtual void invokeStart(ddMouseEvent& event, ddDrawingView *view);
	virtual void invokeStep(ddMouseEvent& event, ddDrawingView *view);
	virtual wxCursor createCursor();
	virtual int getIndex();
	virtual void setIndex(int index);
protected:

private:
	int indx;


};
#endif
