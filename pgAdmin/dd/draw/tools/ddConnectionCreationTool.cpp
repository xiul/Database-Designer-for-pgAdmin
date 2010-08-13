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

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddConnectionCreationTool::ddConnectionCreationTool(ddDrawingEditor *editor, ddLineConnection *figure):
ddAbstractTool(editor)
{
	toolConnection=figure;
	toolConnection->disconnectStart();
	toolConnection->disconnectEnd();
	handle=NULL;
	numClicks=0;
	dragged=false;
}

ddConnectionCreationTool::~ddConnectionCreationTool(){
}

void ddConnectionCreationTool::mouseDrag(ddMouseEvent& event)
{
	if(handle && event.LeftIsDown())
	{
		dragged=true;
		//int x=event.GetPosition().x, y=event.GetPosition().y;
		handle->invokeStep(event,getDrawingEditor()->view());
	}
}

void ddConnectionCreationTool::mouseDown(ddMouseEvent& event)
{
	ddAbstractTool::mouseDown(event);
	if(event.LeftDown())
	{
		numClicks++;
		int x=event.GetPosition().x, y=event.GetPosition().y;
		ddDrawingView *view = getDrawingEditor()->view();
		ddIFigure *figure = view->getDrawing()->findFigure(x,y);

		if(figure)
		{
			if(numClicks==1)  //first mouse click to select start/end figure
			{
				toolConnection->setEndPoint(ddPoint(x,y));
				toolConnection->setStartPoint(ddPoint(x,y));
				toolConnection->connectStart(figure->connectorAt(x,y));
				toolConnection->updateConnection();
				view->add(toolConnection);
				view->clearSelection();
				view->addToSelection(toolConnection);
				handle = toolConnection->getEndHandle();
			}
			else if(numClicks>1) //second mouse click to select end figure only
			{
					toolConnection->setEndPoint(ddPoint(x,y));
					toolConnection->updateConnection();
			}
		}
		else
		{
			//DD-TODO: fix memory leaks when set a tool
			getDrawingEditor()->setTool(new ddSelectionTool(getDrawingEditor()));
		}
	}
}

void ddConnectionCreationTool::mouseUp(ddMouseEvent& event)
{
	if(event.LeftUp())
	{
		//int x=event.GetPosition().x, y=event.GetPosition().y;
		if(handle)
		{
			handle->invokeEnd(event,getDrawingEditor()->view());
		}

		if(toolConnection->getEndConnector()==NULL)
		{
			toolConnection->disconnectStart();
			toolConnection->disconnectEnd();
			getDrawingEditor()->view()->remove(toolConnection);
			getDrawingEditor()->view()->clearSelection();
			//DD-TODO: should I delete here toolConnection???
		}
	}
		//DD-TODO: fix memory leaks when set a tool
	if(dragged || numClicks>1)   //if drag to select a figure or is second or higher click (to select end figure) then this tool ends.
	{
		getDrawingEditor()->setTool(new ddSelectionTool(getDrawingEditor()));
	}
	else if(!dragged && numClicks==1)  //if not dragged before and is first click then allow to select end, disconnecting it
	{
		toolConnection->disconnectEnd();
	}

}

void ddConnectionCreationTool::mouseMove(ddMouseEvent& event)
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

	if(handle && numClicks>0)
	{
		handle->invokeStep(event,getDrawingEditor()->view());
	}


}