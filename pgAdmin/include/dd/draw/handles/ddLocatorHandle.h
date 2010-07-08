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

#ifndef DDLOCATORHANDLE_H
#define DDLOCATORHANDLE_H

#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/locators/ddILocator.h"

class ddDrawingView;  //Hack-Fix to avoid circular reference

class ddLocatorHandle : public ddIHandle
{
public:
	ddLocatorHandle(ddIFigure *owner, ddILocator *locator);
    ~ddLocatorHandle();

	virtual ddPoint& locate();
	virtual ddILocator* locator();
	virtual void invokeStart(int x, int y, ddDrawingView *view);
	virtual void invokeStep(int x, int y, ddDrawingView *view);
	virtual void invokeEnd(int x, int y, ddDrawingView *view);
protected:

private:
	ddILocator *loc;

};
#endif
