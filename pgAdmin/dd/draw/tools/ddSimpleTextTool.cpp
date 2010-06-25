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


ddSimpleTextTool::ddSimpleTextTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
	showEdit = false;
	//DD-TODO: set this value: edit.SetFont();  and fix layout and fix ID of edit because it should be a constant
	edit = new wxTextCtrl(editor->view(),24062010,wxT(""),wxPoint(0,0),wxSize(10,10));
	edit->Connect(24062010,wxEVT_COMMAND_TEXT_UPDATED, (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) &ddSimpleTextTool::changeHandler);
	calculateSizeEntry ();
}

ddSimpleTextTool::~ddSimpleTextTool()
{
	if(edit)
		delete edit;
}

void ddSimpleTextTool::calculateSizeEntry()
{
	int padding = -666; //666 hacer esto ((ddSimpleTextFigure *)this->getFigure())
	ddRect r = figure->displayBox();
	r.Inflate(-padding,-padding);
	//TODO: Translate position when scrolled
	
	edit->SetPosition(r.GetPosition());
	edit->SetSize(r.GetSize());
}

void ddSimpleTextTool::changeHandler(wxCommandEvent& event)
{
/*	ddSimpleTextFigure *txtfigure = (ddSimpleTextFigure *)this->getFigure();
	txtfigure->setText(edit->getValue());
	*/
}

void ddSimpleTextTool::mouseDown(wxMouseEvent& event)
{
}

void ddSimpleTextTool::activate()
{
}

void ddSimpleTextTool::deactivate()
{
}

void ddSimpleTextTool::mouseDrag(wxMouseEvent& event)
{
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