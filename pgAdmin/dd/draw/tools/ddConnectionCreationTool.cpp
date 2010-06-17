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
#include "dd/draw/tools/ddConnectionCreationTool.h"
#include "dd/draw/tools/ddSelectionTool.h"
#include "dd/draw/main/ddDrawingView.h"


ddConnectionCreationTool::ddConnectionCreationTool(ddDrawingEditor *editor, ddIConnectionFigure *figure):
ddAbstractTool(editor)
{
	toolConnection=figure;
	toolConnection->disconnectStart();
	toolConnection->disconnectEnd();
	handle=NULL;
}

ddConnectionCreationTool::~ddConnectionCreationTool(){
}

void ddConnectionCreationTool::mouseDrag(wxMouseEvent& event)
{
	if(handle)
	{
		int x=event.GetPosition().x, y=event.GetPosition().y;
		handle->invokeStep(x,y,getDrawingEditor()->view());
	}
}

void ddConnectionCreationTool::mouseDown(wxMouseEvent& event)
{
	ddAbstractTool::mouseDown(event);
	int x=event.GetPosition().x, y=event.GetPosition().y;
	ddDrawingView *view = getDrawingEditor()->view();
	ddIFigure *figure = view->getDrawing()->findFigure(x,y);

	if(figure)
	{
		toolConnection->setEndPoint(new ddPoint(x,y));
		toolConnection->setStartPoint(new ddPoint(x,y));
		toolConnection->connectStart(figure->connectorAt(x,y));
		toolConnection->updateConnection();
		view->add(toolConnection);
		view->clearSelection();
		view->addToSelection(toolConnection);
		handle = toolConnection->getEndHandle();
	}
	else
	{
		//DD-TODO: fix memory leaks when set a tool
		getDrawingEditor()->setTool(new ddSelectionTool(getDrawingEditor()));
	}
}

void ddConnectionCreationTool::mouseUp(wxMouseEvent& event)
{
	int x=event.GetPosition().x, y=event.GetPosition().y;
	if(handle)
	{
		handle->invokeEnd(x,y,getDrawingEditor()->view());
	}

	if(toolConnection->getEndConnector()==NULL)
	{
		toolConnection->disconnectStart();
		toolConnection->disconnectEnd();
		getDrawingEditor()->view()->remove(toolConnection);
		getDrawingEditor()->view()->clearSelection();
		//DD-TODO: should I delete here toolConnection???
	}
		//DD-TODO: fix memory leaks when set a tool
	getDrawingEditor()->setTool(new ddSelectionTool(getDrawingEditor()));
}

void ddConnectionCreationTool::mouseMove(wxMouseEvent& event)
{
	int x=event.GetPosition().x, y=event.GetPosition().y;
	ddDrawingView *view = getDrawingEditor()->view();
	ddIFigure *figure = view->getDrawing()->findFigure(x,y);
	if(figure)
	{
		getDrawingEditor()->view()->SetCursor(wxCursor(wxCURSOR_PENCIL));
	}
	else
	{
		getDrawingEditor()->view()->SetCursor(wxCursor(wxCURSOR_CROSS));
	}
}