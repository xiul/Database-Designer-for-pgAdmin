//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawing.cpp - Container for figures that send changed events to Listeners whenever 
//	a part of its area was invalidated. Using the design pattern observer to decouple the
//	Drawing from its views and to enable multiple views .
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/textctrl.h>

// App headers
#include "dd/draw/tools/ddSimpleTextTool.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


class ddDrawingEditor;

ddSimpleTextTool::ddSimpleTextTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
	showEdit = false;
	//DD-TODO: set this value: edit.SetFont();  and fix layout and fix ID of edit because it should be a constant
	txtFigure = ((ddSimpleTextFigure *)this->getFigure());
	editor->view()->setSimpleTextToolFigure(NULL);
	edit = getDrawingEditor()->view()->getSimpleTextToolEdit();
	calculateSizeEntry();
	
}

ddSimpleTextTool::~ddSimpleTextTool()
{
}

void ddSimpleTextTool::calculateSizeEntry()
{
	if(edit)
	{
		edit->SetPosition(txtFigure->displayBox().GetPosition());
		edit->SetSize(txtFigure->displayBox().GetSize());
		//DD-TODO: avoid in a future twin function in DrawingView because tool hack
	}
}

void ddSimpleTextTool::mouseDown(wxMouseEvent& event)
{	
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
	if(event.LeftDClick())
	{
		getDrawingEditor()->view()->setSimpleTextToolFigure(txtFigure);
		showEdit = true;
		edit->ChangeValue(txtFigure->getText()); //Same as SetValue but don't generated wxEVT_COMMAND_TEXT_UPDATED event
		calculateSizeEntry();
		edit->SetFocus();
		edit->Show();
		return;
	}
	getDefaultTool()->mouseDown(event);
}

void ddSimpleTextTool::activate()
{
	showEdit = false;
	ddFigureTool::activate();
}

void ddSimpleTextTool::deactivate()
{
	if(edit)
	{
		edit->Hide();  //I can't delete it because view is the owner of this object
		getDrawingEditor()->view()->setSimpleTextToolFigure(NULL);
	}
	ddFigureTool::deactivate();
}

void ddSimpleTextTool::mouseDrag(wxMouseEvent& event)
{
	if(!showEdit)
	{
		getDefaultTool()->mouseDrag(event);
	}
}

/*
ddFigureTool::ddFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddAbstractTool(editor)
{
	defaultTool=dt;
	figure=fig;
}

ddFigureTool::~ddFigureTool(){
	if(defaultTool)
		delete defaultTool;
}

void ddFigureTool::setDefaultTool(ddITool *dt)
{
	defaultTool=dt;
}

ddITool* ddFigureTool::getDefaultTool()
{
	return defaultTool;
}

void ddFigureTool::setFigure(ddIFigure *fig)
{
	figure=fig;
}

ddIFigure* ddFigureTool::getFigure()
{
	return figure;
}

void ddFigureTool::mouseDown(wxMouseEvent& event){
	if(defaultTool)
	{
		defaultTool->mouseDown(event);
	}
}

void ddFigureTool::mouseUp(wxMouseEvent& event){
	if(defaultTool)
	{
		defaultTool->mouseUp(event);
	}
}

void ddFigureTool::mouseMove(wxMouseEvent& event){
	if(defaultTool)
	{
		defaultTool->mouseMove(event);
	}
}

void ddFigureTool::mouseDrag(wxMouseEvent& event){
	if(defaultTool)
	{
		defaultTool->mouseDrag(event);
	}
}

void ddFigureTool::keyDown(wxKeyEvent& event){
	if(defaultTool)
	{
		defaultTool->keyDown(event);
	}
}

void ddFigureTool::keyUp(wxKeyEvent& event)
{
		if(defaultTool)
	{
		defaultTool->keyUp(event);
	}
}
*/