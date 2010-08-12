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

#ifndef DDRELATIONSHIPTERMINAL_H
#define DDRELATIONSHIPTERMINAL_H
#include "dd/draw/figures/ddLineTerminal.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"



class ddRelationshipTerminal : public ddLineTerminal
{
public:
	ddRelationshipTerminal(ddRelationshipFigure *owner, bool endFigureTerminal);
    ~ddRelationshipTerminal();
	virtual ddPoint& draw (wxBufferedDC& context, ddPoint& a, ddPoint& b, ddDrawingView *view);
protected:
	
private:
	double lastFactor;
	ddRelationshipFigure *ownerFigure;
	bool endTerminal;
};
#endif
