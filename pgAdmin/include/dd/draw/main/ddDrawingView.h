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

#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/main/ddDrawing.h"
//#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/draw/figures/ddAbstractMenuFigure.h"
// Create View Class for MVC pattern of graphic library of pgAdmin

class ddDrawingView : public wxScrolledWindow
{
public:
	ddDrawingView(wxWindow *ddParent, ddDrawingEditor *editor ,wxSize size, ddDrawing *drawing);
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
	virtual ddDrawing* getDrawing();
	virtual bool isFigureSelected(ddIFigure *figure);
	void onPaint(wxPaintEvent& event);
	void onEraseBackGround(wxEraseEvent& event);
	virtual ddIteratorBase* selectionFigures();
	virtual void onMouseDown(wxMouseEvent& event);
	virtual void onMouseUp(wxMouseEvent& event);
	//virtual void onRightClick(wxMouseEvent& event);
	virtual void onMotion(wxMouseEvent& event);
	ddDrawingEditor* editor();  
	//virtual void OnKeyDown(wxKeyEvent& event);
	wxSize canvasSize;
	
	//Hack to avoid selection rectangle drawing bug
	void setSelRect(ddRect& selectionRect);
	void disableSelRectDraw();
	//End Hack to avoid selection rectangle drawing bug

	//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event
	void simpleTextToolChangeHandler(wxCommandEvent& event);
	void setSimpleTextToolFigure(ddSimpleTextFigure *figure);
	wxTextCtrl* getSimpleTextToolEdit();
	wxBitmapButton* getOkTxt();
	wxBitmapButton* getCancelTxt();
	//End Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event

	//Hack to allow use (events) of wxmenu inside a tool Generic Way
	void setMenuToolFigure(ddAbstractMenuFigure *figure);
	//End Hack to allow use (events) of wxmenu inside a tool 

	//DD-TODO: Below functions aren't exclusively used by simpletexttool change their names in a more generic way

	//Hack to allow use (events) of wxmenu inside a tool like simpletexttool
	void OnTextPopupClick(wxCommandEvent& event);
	void OnOkTxtButton(wxCommandEvent& event);
	void OnCancelTxtButton(wxCommandEvent& event);
	void setTextPopUpList(wxArrayString &strings, wxMenu &mnu);
	//End Hack to allow use (events) of wxmenu inside a tool like simpletexttool


	/*
	virtual wxPoint drawingToView(double x, double y);
	virtual wxPoint viewToDrawing(double x, double y);
	virtual ddIDrawing* drawing();
	
	virtual int selectionCount();
	virtual ddRect visibleArea();
	*/

protected:

private:
	DECLARE_EVENT_TABLE()
	ddCollection *selection;
	ddDrawing *drawing;
	ddDrawingEditor *drawingEditor;

	//Hack to avoid selection rectangle drawing bug
	ddRect selRect;  
	wxPoint selPoints[5];
	bool drawSelRect;
	//End Hack to avoid selection rectangle drawing bug
	
	//Hack to allow use (events) of wxmenu inside a tool Generic Way
	ddAbstractMenuFigure *menuFigure;
	//End hack to allow use (events) of wxmenu inside a tool Generic Way

	//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event && POPUP EVENT
	wxTextCtrl *simpleTextToolEdit;
	wxBitmapButton *okTxtButton, *cancelTxtButton;
	ddSimpleTextFigure *simpleTextFigure;
	wxString oldText;
	//End Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event && POPUP EVENT
};
#endif
