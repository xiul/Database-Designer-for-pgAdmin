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

#ifndef DDIDRAWINGVIEW_H
#define DDIDRAWINGVIEW_H

#include "dd/draw/ddIFigure.h"
#include "dd/draw/ddIHandle.h"
#include "dd/draw/ddDrawing.h"

// Create Array Objects used as base for gqbCollections
class ddDrawingView : public wxScrolledWindow
{
public:
	ddDrawingView(wxWindow *ddParent, wxSize size, ddDrawing *drawing);
	~ddDrawingView();
	virtual void add(ddIFigure *figure);
	virtual void remove(ddIFigure *figure);
    // ddCollection* insertFigures(ddCollection figures, double dx, double dy, bool check);
	virtual void addToSelection(ddIFigure *figure);
	virtual void addToSelection(ddCollection *figures);
	virtual void removeFromSelection(ddIFigure *figure);
	virtual void toggleSelection(ddIFigure *figure);
	virtual void clearSelection();
	virtual void ScrollToMakeVisible(wxPoint p);
	virtual void ScrollToMakeVisible (ddRect r);
	virtual ddIHandle* findHandle(double x, double y);
	virtual bool isFigureSelected(ddIFigure *figure);
	void onPaint(wxPaintEvent& event);
	virtual ddIteratorBase* selectionFigures();
	wxSize canvasSize;

	/*
	virtual wxPoint drawingToView(double x, double y);
	virtual wxPoint viewToDrawing(double x, double y);
	virtual ddIDrawing* drawing();
	virtual ddIDrawing* editor();   //DD-TODO: debe retornar un editor
	virtual int selectionCount();
	virtual ddRect visibleArea();
	*/

protected:

private:
	DECLARE_EVENT_TABLE()
	ddCollection *selection;
	ddDrawing *drawing;

};
#endif
