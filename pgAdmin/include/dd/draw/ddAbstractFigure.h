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

#ifndef DDABSTRACTFIGURE_H
#define DDABSTRACTFIGURE_H
#include "dd/draw/ddRect.h"
#include "dd/draw/ddIFigure.h"
#include "dd/draw/ddCollection.h"



// Create Array Objects used as base for gqbCollections
class ddAbstractFigure : public ddIFigure
{
public:
	ddAbstractFigure();
    ~ddAbstractFigure();
	
	virtual bool canConnect ();

protected:
		wxColour fillColor, lineColor;
		double lineWidth;

private:

};
#endif
