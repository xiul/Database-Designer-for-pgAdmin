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

#ifndef DDSOUTHTABLESIZEHANDLE_H
#define DDSOUTHTABLESIZEHANDLE_H

#include "dd/draw/handles/ddLocatorHandle.h"

class ddTableFigure;

class ddSouthTableSizeHandle : public ddLocatorHandle
{
public:
	ddSouthTableSizeHandle(ddTableFigure *owner, ddILocator *locator);
    ~ddSouthTableSizeHandle();
	virtual wxCursor createCursor();
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
//	virtual ddPoint* locate();
	virtual ddRect& getDisplayBox();
	virtual void invokeStart(ddMouseEvent &event, ddDrawingView *view);
	virtual void invokeStep(ddMouseEvent &event, ddDrawingView *view);
	virtual void invokeEnd(ddMouseEvent &event, ddDrawingView *view);
protected:

private:
	int anchorY;
/*	ddPoint startPoint, endPoint;
	bool drawTempRect;*/

};
#endif
