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
	if(colTextFigure->ms_classInfo.IsKindOf(&ddTextColumnFigure::ms_classInfo))
		colTextFigure = (ddTextColumnFigure *) fig;
	else
		colTextFigure = NULL;
}

ddColumnTextTool::~ddColumnTextTool()
{
}

void ddColumnTextTool::mouseDown(ddMouseEvent& event)
{	
	//Hack to graphically delete columns
	if(event.LeftDown())
	{
		if(colTextFigure && colTextFigure->getOwnerColumn() && colTextFigure->getOwnerColumn()->getOwnerTable()->deleteColumnActivated())
		{
			if(colTextFigure->getOwnerColumn()->isForeignKey())
			{
				wxMessageBox(wxT("You can't delete column: ")+colTextFigure->getText(true)+ wxT(" because is a foreign key, instead just delete relationship"),wxT("Foreign key information"),wxICON_EXCLAMATION, event.getView());
			}
			else
			{
				ddTableFigure *table = colTextFigure->getOwnerColumn()->getOwnerTable();
				if(getDrawingEditor()->view()->isFigureSelected(table))
				{
					int answer = wxMessageBox(wxT("Delete column: ") + colTextFigure->getText(true) + wxT("?"), wxT("Confirm"),wxYES_NO, event.getView());
					if (answer == wxYES)
					{
						table->removeColumn(colTextFigure->getOwnerColumn());		
						colTextFigure = NULL;
					}
				}
				table->toggleColumnDeleteMode();
			}
			return;
		}

	}
	if(colTextFigure && colTextFigure->getOwnerColumn() &&  colTextFigure->getOwnerColumn()->getOwnerTable()) //if click on any other place disable column delete
		colTextFigure->getOwnerColumn()->getOwnerTable()->toggleColumnDeleteMode(true);
	ddSimpleTextTool::mouseDown(event);
}
