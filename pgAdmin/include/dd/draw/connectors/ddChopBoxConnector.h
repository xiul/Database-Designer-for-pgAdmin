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

#ifndef DDCHOPBOXCONNECTOR_H
#define DDCHOPBOXCONNECTOR_H


#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/figures/ddIFigure.h"
/*-#include "dd/draw/main/ddObject.h"

#include "dd/draw/utilities/ddPoint.h"*/

class ddChopBoxConnector : public ddIConnector
{
public:
	ddChopBoxConnector(ddIFigure *owner);
    ~ddChopBoxConnector();
	virtual ddPoint findStart(ddLineConnection *connFigure);
	virtual ddPoint findEnd(ddLineConnection *connFigure);
/*	virtual bool containsPoint(int x, int y);
	virtual void draw(wxBufferedDC& context)=0;
	virtual ddIFigure* getOwner();
	*/
protected:
	virtual ddPoint chop(ddIFigure *target, ddPoint point);
/*	virtual void setOwner(ddIFigure *owner);
	virtual ddRect& getDisplayBox();
	ddRect displayBox;*/
private:
	//ddIFigure *figureOwner; 

};
#endif
