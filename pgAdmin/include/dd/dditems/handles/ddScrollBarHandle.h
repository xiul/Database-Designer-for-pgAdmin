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

#ifndef DDSCROLLBARHANDLE_H
#define DDSCROLLBARHANDLE_H

#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/handles/ddLocatorHandle.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/dditems/figures/ddTableFigure.h"


class ddScrollBarHandle : public ddIHandle
{
public:
	ddScrollBarHandle(ddTableFigure *owner, ddILocator *scrollBarLocator , wxSize &size);
    ~ddScrollBarHandle();


	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual ddPoint& locate();
	virtual wxCursor createCursor();
	virtual void invokeStart(ddMouseEvent &event, ddDrawingView *view);
	virtual void invokeStep(ddMouseEvent &event, ddDrawingView *view);
	virtual void invokeEnd(ddMouseEvent &event, ddDrawingView *view);
	virtual ddRect& getDisplayBox();
protected:
private:
	ddILocator *scrollLocator;
	ddTableFigure *table;
	wxBitmap upBitmap, downBitmap;
	wxSize barSize;
	int anchorY;

};
#endif
