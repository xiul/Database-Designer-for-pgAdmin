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


class ddScrollBarHandle : public ddIHandle
{
public:
	ddScrollBarHandle(ddIFigure *owner, ddILocator *buttonLocator , wxSize &size);
    ~ddScrollBarHandle();

	//virtual wxCursor& createCursor();
	//virtual ddRect& getDisplayBox();
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual ddPoint& locate();
	virtual void invokeStart(int x, int y, ddDrawingView *view);
	virtual void invokeStep(int x, int y, ddDrawingView *view);
	virtual void invokeEnd(int x, int y, ddDrawingView *view);
protected:
private:
	ddILocator *bLocator;

};
#endif
