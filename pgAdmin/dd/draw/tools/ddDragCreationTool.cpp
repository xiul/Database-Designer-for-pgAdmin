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
#include "dd/draw/tools/ddDragCreationTool.h"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddDragCreationTool::ddDragCreationTool(ddDrawingEditor *editor, ddIFigure *prototype):
ddCreationTool(editor, prototype)
{
}

ddDragCreationTool::~ddDragCreationTool(){
}


void ddDragCreationTool::mouseDrag(ddMouseEvent& event){
	if(event.LeftIsDown())
	{
		figurePrototype->displayBox().SetPosition(event.GetPosition());
	}
}
