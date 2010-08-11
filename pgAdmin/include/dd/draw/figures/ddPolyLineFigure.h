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

#include "dd/draw/figures/ddAbstractMenuFigure.h"
#include "dd/draw/figures/ddLineTerminal.h"
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/utilities/ddPoint.h"

// Create Array Objects used as base for gqbCollections
class ddPolyLineFigure : public ddAbstractMenuFigure
{
public:
	ddPolyLineFigure();
    ~ddPolyLineFigure();

	virtual ddRect& getBasicDisplayBox();
	virtual void basicDraw (wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);
	virtual int pointCount();
	virtual ddPoint& getStartPoint();
	virtual void setStartPoint(ddPoint point);
	virtual ddPoint& getEndPoint();
	virtual void setEndPoint(ddPoint point);
	virtual void setStartTerminal(ddLineTerminal *terminal);
	virtual ddLineTerminal* getStartTerminal();
	virtual void setEndTerminal(ddLineTerminal *terminal);
	virtual ddLineTerminal* getEndTerminal();
	ddCollection* handlesEnumerator();
	virtual int findSegment (int x, int y);
	virtual void splitSegment(int x, int y);
	virtual void changed();

	virtual void addPoint (int x, int y);
//	virtual void removePoint (int index);
	virtual void clearPoints ();
	virtual void insertPointAt (int index, int x, int y);
	virtual void setPointAt (int index, int x, int y);
	virtual void removePointAt (int index);
	virtual void basicMoveBy(int x, int y);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);

	virtual ddPoint& pointAt(int index);
	virtual bool containsPoint (int x, int y);
	virtual void setLinePen(wxPen pen);

protected:
	//DD-TODO: need to store dashes?
	virtual void updateHandlesIndexes();
	ddArrayCollection *points;
	ddPoint endPoint, startPoint, pointAtPos;
private:
	ddLineTerminal *startTerminal, *endTerminal;
	bool handlesChanged;//, primero;
	wxPen linePen;

};
#endif
