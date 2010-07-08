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

#ifndef DDPOLYLINELOCATOR_H
#define DDPOLYLINELOCATOR_H

#include "dd/draw/locators/ddILocator.h"

class ddPolyLineLocator : public ddILocator
{
public:
	ddPolyLineLocator(int index);
    ~ddPolyLineLocator();

	virtual ddPoint& locate(ddIFigure *owner);
	virtual void setIndex(int index);

protected:

private:
	int indx;
};
#endif
