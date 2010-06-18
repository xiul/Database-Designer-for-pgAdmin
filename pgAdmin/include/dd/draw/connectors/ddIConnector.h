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

#ifndef DDICONNECTOR_H
#define DDICONNECTOR_H

#include "dd/draw/main/ddObject.h"
//#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"

class ddLineConnection;  //HACK-FIX to circular reference
class ddIFigure;

class ddIConnector : public ddObject
{
public:
	ddIConnector(ddIFigure *owner);
    ~ddIConnector();
	virtual ddPoint findStart(ddLineConnection *connection);
	virtual ddPoint findEnd(ddLineConnection *connection);
	virtual bool containsPoint(int x, int y);
	virtual void draw(wxBufferedDC& context);
	virtual ddIFigure* getOwner();
	virtual ddRect& getDisplayBox();
protected:
	virtual void setOwner(ddIFigure *owner);
	ddRect displayBox;
private:
	ddIFigure *figureOwner; 

};
#endif
