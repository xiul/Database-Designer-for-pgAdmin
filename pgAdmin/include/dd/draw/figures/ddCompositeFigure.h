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

#ifndef DDCOMPOSITEFIGURE_H
#define DDCOMPOSITEFIGURE_H
#include "dd/draw/figures/ddAbstractFigure.h"
/*#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/utilities/ddCollection.h"
*/


// Create Array Objects used as base for gqbCollections
class ddCompositeFigure : public ddAbstractFigure
{
public:
	ddCompositeFigure();
    ~ddCompositeFigure();
	virtual void basicMoveBy(int x, int y);
	virtual bool containsPoint(int x, int y);
	virtual ddIteratorBase* figuresEnumerator();
	virtual ddIteratorBase* figuresInverseEnumerator();
	virtual ddRect& getBasicDisplayBox();
	virtual ddCollection* handlesEnumerator();
	virtual void add(ddIFigure *figure);
	virtual void remove(ddIFigure *figure);
	virtual bool includes(ddIFigure *figure);
	virtual void draw(wxBufferedDC& context);
	virtual void drawSelected(wxBufferedDC& context);
	virtual ddIFigure* findFigure(int x, int y);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	virtual void sendToBack(ddIFigure *figure);
	virtual void sendToFront(ddIFigure *figure);
protected:

private:
	ddCollection *figureFigures;
	ddCollection *figureHandles;

/*	virtual bool canConnect ();
	virtual void draw(wxBufferedDC& context);
	virtual void basicDrawSelected(wxBufferedDC& context);
	virtual bool includes(ddIFigure *figure);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	virtual void moveBy(int x, int y);
	
	virtual void moveTo(int x, int y);
	
	virtual void onFigureChanged(ddIFigure *figure);

//DD-TODO: public virtual IConnector ConnectorAt (double x, double y)
//DD-TODO: public void Visit (IFigureVisitor visitor) 
//DD-TODO: public event EventHandler <FigureEventArgs> FigureInvalidated;
//DD-TODO: public event EventHandler <FigureEventArgs> FigureChanged;

protected:
		virtual void basicDraw(wxBufferedDC& context);
		virtual void drawSelected(wxBufferedDC& context);
		void willChange();
		void changed();
		void invalidate();
		//DD-TODO: OnFigureChanged event implement


		wxColour fillColor, lineColor;
		double lineWidth;

private:
*/
};
#endif
