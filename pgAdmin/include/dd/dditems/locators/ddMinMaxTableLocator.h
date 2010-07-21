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

#ifndef DDMINMAXTABLELOCATOR_H
#define DDMINMAXTABLELOCATOR_H

#include "dd/draw/locators/ddILocator.h"
#include "dd/draw/figures/ddIFigure.h"

class ddMinMaxTableLocator : public ddILocator
{
public:
	ddMinMaxTableLocator();
    ~ddMinMaxTableLocator();

	virtual ddPoint& locate(ddIFigure *owner);

protected:

private:
};
#endif
