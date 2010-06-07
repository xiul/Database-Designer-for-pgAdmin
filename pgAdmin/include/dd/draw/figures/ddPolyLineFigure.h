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

#ifndef DDPOLYLINEFIGURE_H
#define DDPOLYLINEFIGURE_H

#include "dd/draw/figures/ddAbstractFigure.h"
#include "dd/draw/figures/ddLineTerminal.h"
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/utilities/ddPoint.h"

// Create Array Objects used as base for gqbCollections
class ddPolyLineFigure : public ddAbstractFigure
{
public:
	ddPolyLineFigure();
    ~ddPolyLineFigure();

	virtual ddRect& basicDisplayBox();
	virtual void basicDraw (wxBufferedDC& context);
	virtual int pointCount();
	virtual ddPoint* getStartPoint();
	virtual void setStartPoint(ddPoint *point);
	virtual ddPoint* getEndPoint();
	virtual void setEndPoint(ddPoint *point);
	virtual void setStartTerminal(ddLineTerminal *terminal);
	virtual ddLineTerminal* getStartTerminal();
	virtual void setEndTerminal(ddLineTerminal *terminal);
	virtual ddLineTerminal* getEndTerminal();
	ddCollection* handlesEnumerator();

	virtual void addPoint (int x, int y);
	virtual void moveBy(int x, int y);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);

	virtual ddPoint* pointAt(int index);


/*	
	virtual void drawSelected (wxBufferedDC& context);
	virtual ddCollection* handlesEnumerator();
	virtual void addDependentFigure (ddIFigure *figure);
	virtual void removeDependentFigure (ddIFigure *figure);
	virtual void addHandle (ddIHandle *handle);
	virtual void removeHandle (ddIHandle *handle);
	virtual bool containsPoint(int x, int y)=0;
	virtual void moveTo(int x, int y);
	
	virtual bool isSelected();
	virtual void setSelected(bool value);
	
	
*/
protected:
	ddRect basicDisplayBoxRect;
	//DD-TODO: need to store dashes?
private:
	ddArrayCollection *points;
	ddLineTerminal *startTerminal, *endTerminal;
};
#endif
