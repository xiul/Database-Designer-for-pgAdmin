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
#include <wx/choicdlg.h>

// App headers
#include "dd/dditems/tools/ddColumnTextTool.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/figures/ddTableFigure.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


class ddDrawingEditor;


ddColumnTextTool::ddColumnTextTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddSimpleTextTool(editor,fig,dt)
{
	colFigure = (ddColumnFigure *) fig;
}

ddColumnTextTool::~ddColumnTextTool()
{
}

void ddColumnTextTool::mouseDown(ddMouseEvent& event)
{	
	if(event.LeftDown())
	{
		if(colFigure && colFigure->getOwnerTable()->deleteColumnActivated())
		{
			ddTableFigure *table = colFigure->getOwnerTable();
			table->removeColumn(colFigure);
			colFigure = NULL;

			preguntar si se quiere borrar la columna o no antes de hacerlo, mostrar de algun modo en la figura
				que se esta en modo de borrar columna


			table->toggleColumnDeleteMode();
			return;
		}
	}
	ddSimpleTextTool::mouseDown(event);
}

