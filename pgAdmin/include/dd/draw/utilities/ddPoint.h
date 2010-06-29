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

#ifndef DDPOINT_H
#define DDPOINT_H

class ddPoint : public wxPoint{
public:
	ddPoint();
	ddPoint(int x, int y);
	ddPoint(const ddPoint& p);
	ddPoint(const wxPoint& p);
};

#endif
