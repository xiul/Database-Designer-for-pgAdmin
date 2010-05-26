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


class ddRect : public wxRect
{
public:
	ddRect();
	void add (ddRect *newRect);
protected:

private:
	int min(int a, int b);
	int max(int a, int b);
};
#endif
