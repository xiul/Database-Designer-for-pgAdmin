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

#ifndef DDADDFKLOCATOR_H
#define DDADDFKLOCATOR_H

#include "dd/draw/locators/ddILocator.h"
#include "dd/draw/figures/ddIFigure.h"

class ddAddFkLocator : public ddILocator
{
public:
	ddAddFkLocator();
    ~ddAddFkLocator();

	virtual ddPoint& locate(ddIFigure *owner);

protected:

private:
};
#endif
