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

#ifndef DDLINECONNECTIONHANDLE
#define DDLINECONNECTIONHANDLE

#include "dd/draw/handles/ddPolyLineHandle.h"

/*
class ddDrawingView;  //Hack-Fix to avoid circular reference
class ddPolyLineFigure;
*/
class ddLineConnectionHandle : public ddPolyLineHandle
{
public:
	ddLineConnectionHandle(ddPolyLineFigure *figure, ddILocator *loc, int index);
	virtual void invokeEnd(ddMouseEvent& event, ddDrawingView *view);
private:

};
#endif
