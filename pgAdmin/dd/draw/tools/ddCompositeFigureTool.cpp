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

// App headers
#include "dd/draw/tools/ddCompositeFigureTool.h"
#include "dd/draw/figures/ddCompositeFigure.h"


ddCompositeFigureTool::ddCompositeFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
	delegateTool = NULL;
}

ddCompositeFigureTool::~ddCompositeFigureTool()
{
}

void ddCompositeFigureTool::setDefaultTool(ddITool *dt)
{
	ddFigureTool::setDefaultTool(dt);
}

ddITool* ddCompositeFigureTool::getDefaultTool()
{
	if(delegateTool)
	{
		return delegateTool;
	}
	else
	{
		return ddFigureTool::getDefaultTool();
	}
}

void ddCompositeFigureTool::mouseDown(wxMouseEvent& event)
{
	int x=event.GetPosition().x, y=event.GetPosition().y;
	ddCompositeFigure *cfigure = (ddCompositeFigure*) getFigure();
	ddIFigure *figure = cfigure->findFigure(x,y);
	
	if(figure)
	{
		setDelegateTool(figure->CreateFigureTool(getDrawingEditor(),getDefaultTool()));
	}
	else
	{
		setDelegateTool(getDefaultTool());
	}

	if(delegateTool)
	{
		delegateTool->mouseDown(event);
	}
}

void ddCompositeFigureTool::activate()
{
	if(delegateTool)
	{
		delegateTool->activate();
	}
}

void ddCompositeFigureTool::deactivate()
{
	if(delegateTool)
	{
		delegateTool->deactivate();
	}
}

void ddCompositeFigureTool::setDelegateTool(ddITool *tool)
{
	if(delegateTool)
	{
		delegateTool->deactivate();
		delete delegateTool;
	}
	
	delegateTool=tool;
	if(delegateTool)
	{
		delegateTool->activate();
	}
}

ddITool* ddCompositeFigureTool::getDelegateTool()
{
	return delegateTool;
}

/*
void ddSelectionTool::setDelegateTool(ddITool *tool){
	if(_delegateTool){
		_delegateTool->deactivate();
		delete _delegateTool;
	}

	_delegateTool = tool;
	
	if(_delegateTool){
		_delegateTool->activate();
	}
}

ddITool* ddSelectionTool::getDelegateTool(){
	return _delegateTool;
}

void ddSelectionTool::deleteFigures(ddDrawingView *view){
	view->clearSelection();
	view->getDrawing()->deleteFigures();
}
/*
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