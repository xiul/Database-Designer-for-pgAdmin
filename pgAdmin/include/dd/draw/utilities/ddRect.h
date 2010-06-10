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

#ifndef DDRECT_H
#define DDRECT_H
#include "dd/draw/utilities/ddPoint.h"

class ddRect : public wxRect
{
public:
	ddRect();
	ddRect(int xx, int yy, int ww, int hh);
	ddRect(ddPoint *topLeft, ddPoint *bottomRight);
	ddRect(ddPoint *point);
	ddRect(ddPoint &point);
	void add (int newX, int netY);
	void add (ddRect *newRect);
	void add (ddRect& newRect);
	void add (ddPoint *p);
protected:

private:
	int min(int a, int b);
	int max(int a, int b);  //DD-TODO: delete this functions use ddGeometry instead of.
};
#endif
