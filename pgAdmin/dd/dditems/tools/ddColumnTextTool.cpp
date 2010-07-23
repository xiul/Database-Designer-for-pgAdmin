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
#include "dd/dditems/figures/ddTextColumnFigure.h"
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
	if(colFigure->ms_classInfo.IsKindOf(&ddTextColumnFigure::ms_classInfo))
		colFigure = (ddTextColumnFigure *) fig;
	else
		colFigure = NULL;
}

ddColumnTextTool::~ddColumnTextTool()
{
}

void ddColumnTextTool::mouseDown(ddMouseEvent& event)
{	
	if(event.LeftDown())
	{
		if(colFigure && colFigure->getOwnerTable() && colFigure->getOwnerTable()->deleteColumnActivated())
		{
			ddTableFigure *table = colFigure->getOwnerTable();
			if(getDrawingEditor()->view()->isFigureSelected(table))
			{
				int answer = wxMessageBox(wxT("Delete column: ") + colFigure->getText(true) + wxT("?"), wxT("Confirm"),wxYES_NO, event.getView());
				if (answer == wxYES)
				{
			//666 arreglar esto pero ya osea		table->removeColumn(colFigure);		
					colFigure = NULL;
				}
			}
			table->toggleColumnDeleteMode();
			return;
		}

	}
	
	if(colFigure && colFigure->getOwnerTable()) //if click on any other place disable column delete
		colFigure->getOwnerTable()->toggleColumnDeleteMode(true);
	ddSimpleTextTool::mouseDown(event);
}
