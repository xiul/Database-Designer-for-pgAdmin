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

#ifndef DDIFIGURE_H
#define DDIFIGURE_H
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/main/ddObject.h"
#include "dd/draw/utilities/ddCollection.h"
#include "dd/draw/handles/ddIHandle.h"
//#include "dd/draw/connectors/ddIConnector.h"


class ddITool;			// HACK-FIX circular reference
class ddDrawingEditor;
class ddIConnector;
class ddITool;

class ddIFigure : public ddObject
{
public:
	ddIFigure();
    ~ddIFigure();

	virtual ddRect& displayBox();
	virtual ddRect& getBasicDisplayBox();
	virtual void draw (wxBufferedDC& context, ddDrawingView *view);
	virtual void drawSelected (wxBufferedDC& context, ddDrawingView *view);
	virtual ddCollection* handlesEnumerator();
//	virtual void addDependentFigure (ddIFigure *figure);
//	virtual void removeDependentFigure (ddIFigure *figure);
	virtual void addHandle (ddIHandle *handle);
	virtual void removeHandle (ddIHandle *handle);
	ddIConnector* connectorAt (int x, int y);
	virtual void moveBy(int x, int y);
	virtual void moveTo(int x, int y);
	virtual bool containsPoint(int x, int y);
	virtual bool isSelected();
	virtual void setSelected(bool value);
	virtual bool includes(ddIFigure *figure);
	virtual bool canConnect()=0;
	virtual void onFigureChanged(ddIFigure *figure)=0;
	virtual void addObserver (ddIFigure *observer);
	virtual void removeObserver (ddIFigure *observer);	
	virtual ddIteratorBase* observersEnumerator();

	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);

protected:
	ddRect basicDisplayBox;
	ddCollection *figures;
	ddCollection *handles;
//	ddCollection *dependentFigures;
	ddCollection *observers;
	void setDefaultPen(wxPen& pen);
	void setDefaultSelectedPen(wxPen& pen);
	void setDefaultBrush(wxBrush& brush);
	void setDefaultSelectedBrush(wxBrush& brush);
	wxPen defaultPen, defaultSelectedPen;
	wxBrush defaultBrush, defaultSelectedBrush;
private:
	bool selected;
	ddIConnector *connector;

};
#endif
