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

#ifndef DDILOCATOR_H
#define DDILOCATOR_H

#include "dd/draw/main/ddObject.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/figures/ddIFigure.h"

class ddILocator : public ddObject
{
public:
	ddILocator();
    ~ddILocator();

	virtual ddPoint& locate(ddIFigure *owner)=0;

protected:
	ddPoint locatePoint;
private:

};
#endif
