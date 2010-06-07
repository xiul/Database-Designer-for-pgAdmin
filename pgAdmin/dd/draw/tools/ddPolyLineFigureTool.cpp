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
#include "dd/draw/tools/ddPolyLineFigureTool.h"
#include "dd/draw/tools/ddFigureTool.h"
#include "dd/draw/figures/ddPolyLineFigure.h"


ddPolyLineFigureTool::ddPolyLineFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{

}

ddPolyLineFigureTool::~ddPolyLineFigureTool(){
}

void ddPolyLineFigureTool::mouseDown(wxMouseEvent& event){
	int x=event.GetPosition().x, y=event.GetPosition().y;
	setAnchorCoords(x,y);
	//getDrawingEditor()->view();
	//DD-TODO: middle down or right and left down?
	if(event.MiddleDown()){
		ddPolyLineFigure *connection = (ddPolyLineFigure*) figure;
		//HIGH-PRIORITY-FINISH-THIS finalizar
	}

}
