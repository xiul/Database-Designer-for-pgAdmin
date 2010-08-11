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

#ifndef DDLINETERMINAL_H
#define DDLINETERMINAL_H
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/utilities/ddPoint.h"



// Create Array Objects used as base for gqbCollections
class ddLineTerminal : public ddObject
{
public:
	ddLineTerminal();
    ~ddLineTerminal();

	virtual ddPoint& draw (wxBufferedDC& context, ddPoint& a, ddPoint& b, ddDrawingView *view);
	virtual void setLinePen(wxPen pen);
protected:
	wxPen terminalLinePen;	
private:
	ddPoint middle;

};
#endif
