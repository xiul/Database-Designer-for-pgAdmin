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
#include "dd/dditems/figures/ddTextColumnFigure.h"
#include "dd/dditems/tools/ddColumnTextTool.h"
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

ddTextColumnFigure::ddTextColumnFigure(wxString& columnName, ddDataType dataType, ddColumnFigure *owner):
ddSimpleTextFigure(columnName)
{
	columnType = dataType;
	this->setEditable(true);
	enablePopUp();
	ownerColumn = owner;
	showDataType = true;
	recalculateDisplayBox();
}

ddTextColumnFigure::~ddTextColumnFigure()
{

}

wxString& ddTextColumnFigure::getText(bool extended)
{
	if(showDataType && extended)
	{
		wxString ddType = dataTypes()[columnType];
		out = wxString( ddSimpleTextFigure::getText() + wxString(wxT(" : ")) + ddType );
		return  out;
	}
	else
	{
		return ddSimpleTextFigure::getText();
	}
}

//event ID must match enum ddDataType!!! this event was created on view
void ddTextColumnFigure::OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	wxTextEntryDialog *nameDialog=NULL;
	//DD-TODO: improve this
	switch(event.GetId())
	{
		case 0:  // Add Column
			//columnType = dt_null;
			getOwnerColumn()->getOwnerTable()->addColumn(new ddColumnFigure(wxString(wxT("NewColumn")),getOwnerColumn()->getOwnerTable()));
			break;
		case 1:  // Delete Column
			getOwnerColumn()->getOwnerTable()->removeColumn(getOwnerColumn());
			break;
		case 2:  //Rename Column
			nameDialog = new wxTextEntryDialog(view,wxT("Input column name"),wxT("Rename Column"),getText());
			nameDialog->ShowModal();
			setText(nameDialog->GetValue());
			delete nameDialog;
			break;
		case 4:  //Not Null
			getOwnerColumn()->setColumnOption(notnull);
			break;
		case 5:	//Null
			if(!getOwnerColumn()->isPrimaryKey())
				getOwnerColumn()->setColumnOption(null);
			break;
		//DD-TODO: add options for fk, fkpk, fkuk
		case 7:	//pk
			getOwnerColumn()->setColumnKind(pk);
			getOwnerColumn()->setColumnOption(notnull);
			break;
		case 8:	//uk
			getOwnerColumn()->setColumnKind(uk);
			break;
		case 9:	//none
			getOwnerColumn()->setColumnKind(none);
			break;		
		
		case 12:  // Submenu opcion 1
			columnType = dt_bigint;
			break;
		case 13:
			columnType = dt_boolean;
		break;
		case 14:
			columnType = dt_integer;
		break;
		case 15:
			columnType = dt_money;
		break;
		case 16:
			columnType = dt_varchar;
		break;
		case 17: //Call datatypes selector
			//DD-TODO: Add all types, improve and separate from quick access types
			columnType = (ddDataType) wxGetSingleChoiceIndex(wxT("Select column datatype"),wxT("Column Datatypes"),dataTypes());
		break;
	}		
}

//must match enum ddDataType!!!
//It's a lot faster to use constant strings that create it at fly.
wxArrayString& ddTextColumnFigure::popupStrings()
{
		strings.Clear();
		strings.Add(wxT("Add Column"));  //0
		strings.Add(wxT("Delete Column"));  //1
		strings.Add(wxT("Rename Column (N/A, just double click)"));  //2
		
		strings.Add(wxT("--separator--"));

		if(getOwnerColumn()->isNotNull())	//4
			strings.Add(wxT("--checked**Not Null")); 
		else
			strings.Add(wxT("Not Null"));
		
		if(getOwnerColumn()->isNull())	//5
			strings.Add(wxT("--checked**Null"));
		else
			strings.Add(wxT("Null"));

		strings.Add(wxT("--separator--"));

		if(getOwnerColumn()->isPrimaryKey())	//7
			strings.Add(wxT("--checked**Primary Key"));
		else
			strings.Add(wxT("Primary Key"));

		if(getOwnerColumn()->isUniqueKey())		//8
			strings.Add(wxT("--checked**Unique"));
		else
			strings.Add(wxT("Unique"));

		if(getOwnerColumn()->isPlain())		//9
			strings.Add(wxT("--checked**None"));
		else
			strings.Add(wxT("None"));

		strings.Add(wxT("--separator--"));

		strings.Add(wxT("--submenu##Change Column Datatype**Select a Datatype:"));
		
		if(columnType==dt_bigint)		//12
			strings.Add(wxT("--subitem--checked**Bigint"));
		else
			strings.Add(wxT("--subitem**Bigint"));

		if(columnType==dt_boolean)		//13
			strings.Add(wxT("--subitem--checked**Boolean"));
		else
			strings.Add(wxT("--subitem**Boolean"));

		if(columnType==dt_integer)		//14
			strings.Add(wxT("--subitem--checked**Integer"));
		else
			strings.Add(wxT("--subitem**Integer"));

		if(columnType==dt_money)		//15
			strings.Add(wxT("--subitem--checked**Money"));
		else
			strings.Add(wxT("--subitem**Money"));

		if(columnType==dt_varchar)		//16
			strings.Add(wxT("--subitem--checked**Varchar(1)"));   
		else
			strings.Add(wxT("--subitem**Varchar(1)"));   

		strings.Add(wxT("--subitem**Choose another datatype"));   //17
		//DD-TODO: after add varchar left a cursor over length selected to allow used
	//}
	return strings;
};


wxArrayString& ddTextColumnFigure::dataTypes()
{
	//fill popup strings only first time
	if(datatypes.Count()<=0){
		datatypes.Clear();
		datatypes.Add(wxT("Not Defined"));
		datatypes.Add(wxT("Bigint"));
		datatypes.Add(wxT("Boolean"));
		datatypes.Add(wxT("Integer"));
		datatypes.Add(wxT("Money"));
		datatypes.Add(wxT("Varchar(1)"));
		//DD-TODO: after add varchar left a cursor over length selected to allow used
	}
	return datatypes;

}

//DD-TODO: when a event onfigurechange exists, replace this hack with that event
//Hack to allow column text to submit new size of text signal to tablefigure and then recalculate displaybox
void ddTextColumnFigure::setText(wxString textString)
{
	ddSimpleTextFigure::setText(textString);
	if(ownerColumn)
	{
		ownerColumn->displayBoxUpdate();
		ownerColumn->getOwnerTable()->updateTableSize();
	}
}

ddColumnFigure* ddTextColumnFigure::getOwnerColumn()
{
	return ownerColumn;
}

void ddTextColumnFigure::setOwnerColumn(ddColumnFigure *column)
{
	ownerColumn = column;
}

void ddTextColumnFigure::setShowDataType(bool value)
{
	showDataType = value;
}

ddITool* ddTextColumnFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return textEditable ? new ddColumnTextTool(editor,this,defaultTool) : defaultTool;
}

int ddTextColumnFigure::getTextWidth()
{
	int w,h;
	getFontMetrics(w,h);
	return w;
}

int ddTextColumnFigure::getTextHeight()
{
	int w,h;
	getFontMetrics(w,h);
	return h;
}
