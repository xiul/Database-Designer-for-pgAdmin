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

#ifndef DDREMOVECOLBUTTONHANDLE_H
#define DDREMOVECOLBUTTONHANDLE_H

#include "dd/draw/handles/ddButtonHandle.h"

//class ddDrawingView;  //Hack-Fix to avoid circular reference
//class ddIFigure;

class ddRemoveColButtonHandle : public ddButtonHandle
{
public:
	ddRemoveColButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size);
    ~ddRemoveColButtonHandle();

//	virtual wxCursor& createCursor();
//	virtual ddRect& getDisplayBox();
//	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
//	virtual ddPoint* locate();
	virtual void invokeStart(int x, int y, ddDrawingView *view);
	virtual void invokeStep(int x, int y, ddDrawingView *view);
	virtual void invokeEnd(int x, int y, ddDrawingView *view);
protected:

private:

};
#endif
