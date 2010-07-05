//////////////////	////////////////////////////////////////////////////////
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
#include <wx/dcbuffer.h>

// App headers
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/dditems/figures/ddTableFigure.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks

//DD-TODO: Add composite column functionality by addin subcolumn for
//         composite types, but care: composite types can be recursive (using inside other composite types)

ddColumnFigure::ddColumnFigure(wxString& columnName, ddDataType dataType):
ddSimpleTextFigure(columnName)
{
	columnType = dataType;
	this->setEditable(true);
	enablePopUp();
	ownerTable = NULL;
	recalculateDisplayBox();
}



ddColumnFigure::~ddColumnFigure()
{

}

wxString& ddColumnFigure::getText(bool extended)
{
	if(extended)
	{
		wxString ddType = popupStrings()[columnType];
		out = wxString( ddSimpleTextFigure::getText() + wxString(wxT(" : ")) + ddType );
		return  out;
	}
	else
	{
		return ddSimpleTextFigure::getText();
	}
}

//event ID must match enum ddDataType!!! this event was created on view
void ddColumnFigure::OnTextPopupClick(wxCommandEvent& event)
{
	//DD-TODO: improve this
	switch(event.GetId())
	{
		case 0:
			columnType = dt_bigint;
		break;
		case 1:
			columnType = dt_boolean;
		break;
		case 2:
			columnType = dt_bool;
		break;
		case 3:
			columnType = dt_integer;
		break;
		case 4:
			columnType = dt_money;
		break;
		case 5:
			columnType = dt_varchar_n;
		break;
	}		
}

//must match enum ddDataType!!!
wxArrayString& ddColumnFigure::popupStrings()
{
	//fill popup strings only first time
	if(strings.Count()<=0){
		strings.Clear();
		strings.Add(wxT("BIGINT"));
		strings.Add(wxT("BOOLEAN"));
		strings.Add(wxT("BOOL"));
		strings.Add(wxT("INTEGER"));
		strings.Add(wxT("MONEY"));
		strings.Add(wxT("VARCHAR("));
	}
	return strings;
};

//DD-TODO: when a event onfigurechange exists, replace this hack with that event
//Hack to allow column text to submit new size of text signal to tablefigure and then recalculate displaybox
void ddColumnFigure::setText(wxString textString)
{
	ddSimpleTextFigure::setText(textString);
	if(ownerTable)
		ownerTable->updateTableSize();

}

ddTableFigure* ddColumnFigure::getOwnerTable()
{
	return ownerTable;
}

void ddColumnFigure::setOwnerTable(ddTableFigure *table)
{
	ownerTable = table;
}