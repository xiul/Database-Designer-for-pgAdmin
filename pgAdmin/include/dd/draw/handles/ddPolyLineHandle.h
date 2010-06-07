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

class ddPolyLineHandle : public ddIHandle
{
public:
	ddPolyLineHandle(ddPolyLineFigure *figure, ddILocator *loc, int index);
    ~ddPolyLineHandle();

	virtual bool containsPoint(double x, double y);
	virtual void draw(wxBufferedDC& context);
	virtual ddPoint* locate();
	virtual void invokeStart(int x, int y, ddDrawingView *view);
	virtual void invokeStep(int x, int y, ddDrawingView *view);
	virtual void invokeEnd(int x, int y, ddDrawingView *view);
	virtual wxCursor& createCursor();
protected:

private:
	int indx;


};
#endif
