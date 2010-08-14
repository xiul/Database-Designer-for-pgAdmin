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
	wxString tmpString;
	int answer;
	//DD-TODO: improve this
	switch(event.GetId())
	{
		case 0:  // Add Column
				getOwnerColumn()->getOwnerTable()->addColumn(new ddColumnFigure(wxString(wxT("NewColumn")),getOwnerColumn()->getOwnerTable()));
				break;
		case 1:  // Delete Column
				answer = wxMessageBox(wxT("Delete column: ") + getText(true) + wxT("?"), wxT("Confirm"),wxYES_NO, view);
				if (answer == wxYES)
				{
					getOwnerColumn()->getOwnerTable()->removeColumn(getOwnerColumn());
				}
				break;
		case 2:  //Rename Column
				nameDialog = new wxTextEntryDialog(view,wxT("Input column name"),wxT("Rename Column"),getText());   //DD-TODO: change for dialog like in option 17
				nameDialog->ShowModal();
				setText(nameDialog->GetValue());
				delete nameDialog;
				break;
		case 4:  //Not Null
				if(getOwnerColumn()->isNotNull())
					getOwnerColumn()->setColumnOption(null);
				else
					getOwnerColumn()->setColumnOption(notnull);
				break;
				//DD-TODO: add options fr fk, fkpk, fkuk
		case 6:	//pk
				if(getOwnerColumn()->isPrimaryKey())
				{
					getOwnerColumn()->setColumnKind(none);
				}else
				{	
					getOwnerColumn()->setColumnKind(pk);
					getOwnerColumn()->setColumnOption(notnull);
				}
				break;
		case 7:	//uk
				getOwnerColumn()->setColumnKind(uk,view);
				break;
		case 10:  // Submenu opcion 1
				columnType = dt_bigint;
				break;
		case 11:
				columnType = dt_boolean;
		break;
		case 12:
				columnType = dt_integer;
		break;
		case 13:
				columnType = dt_money;
		break;
		case 14:
				columnType = dt_varchar;
		break;
		case 15: //Call datatypes selector
				//DD-TODO: Add all types, improve and separate from quick access types
				columnType = (ddDataType) wxGetSingleChoiceIndex(wxT("Select column datatype"),wxT("Column Datatypes"),dataTypes(),view);
		break;
		case 17:
				tmpString=wxGetTextFromUser(wxT("Change name of Primary Key constraint:"),getOwnerColumn()->getOwnerTable()->getPkConstraintName(),getOwnerColumn()->getOwnerTable()->getPkConstraintName(),view);
				if(tmpString.length()>0)
					getOwnerColumn()->getOwnerTable()->setPkConstraintName(tmpString);
				break;
		case 18:
				answer = wxGetSingleChoiceIndex(wxT("Select Unique Key constraint to edit name"),wxT("Select Unique Constraint to edit name:"),getOwnerColumn()->getOwnerTable()->getUkConstraintsNames(),view);
				if(answer>=0)
				{
					tmpString=wxGetTextFromUser(wxT("Change name of Unique Key constraint:"),getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Item(answer),getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Item(answer),view);
					if(tmpString.length()>0)
						getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Item(answer)=tmpString;
				}
				break;
		case 20:
				answer = wxMessageBox(wxT("Delete Table: ") + getOwnerColumn()->getOwnerTable()->getTableName() + wxT("?"), wxT("Confirm"),wxYES_NO, view);
				if (answer == wxYES)
				{
					ddTableFigure *table = getOwnerColumn()->getOwnerTable();	
					//unselect table
					if(view->isFigureSelected(table))
					{
						view->removeFromSelection(table);
					}
					//drop foreign keys relationship from others table (this table have the fks)
					table->processDeleteAlert(view);
					//drop table
					view->remove(table);
					if(table)
					{
						delete table;
					}						
				}

	}		
}

//must match enum ddDataType!!!
//It's a lot faster to use constant strings that create it at fly.
wxArrayString& ddTextColumnFigure::popupStrings()
{
		strings.Clear();
		strings.Add(wxT("Add a column ..."));  //0
		if(getOwnerColumn()->isForeignKey())
		{
			strings.Add(wxT("--disable**Delete a column ..."));  //1
		}
		else
		{
			strings.Add(wxT("Delete a column ..."));  //1
		}
		strings.Add(wxT("Rename a column ..."));  //2
		
		strings.Add(wxT("--separator--"));

		if(getOwnerColumn()->isNotNull())	//4
		{
			if(getOwnerColumn()->isForeignKey())
				strings.Add(wxT("--checked--disable**Not Null")); 
			else
				strings.Add(wxT("--checked**Not Null")); 
		}
		else
		{
			if(getOwnerColumn()->isForeignKey())		
				strings.Add(wxT("--disable**Not Null"));
			else
				strings.Add(wxT("Not Null"));
		}
		
		strings.Add(wxT("--separator--"));

		if(getOwnerColumn()->isPrimaryKey())	//6
		{
			if(getOwnerColumn()->isForeignKey())	
				strings.Add(wxT("--checked--disable**Primary Key"));
			else
				strings.Add(wxT("--checked**Primary Key"));
		}
		else
		{
			if(getOwnerColumn()->isForeignKey())	
				strings.Add(wxT("--disable**Primary Key"));
			else
				strings.Add(wxT("Primary Key"));
		}

		if(getOwnerColumn()->isUniqueKey())		//7
			strings.Add(wxT("--checked**Unique"));
		else
			strings.Add(wxT("Unique..."));

		strings.Add(wxT("--separator--"));

		if(getOwnerColumn()->isForeignKey())	
			strings.Add(wxT("--disable--submenu##Change Column Datatype**Select a Datatype:"));
		else
			strings.Add(wxT("--submenu##Change Column Datatype**Select a Datatype:"));
		
		if(columnType==dt_bigint)		//10
			strings.Add(wxT("--subitem--checked**Bigint"));
		else
			strings.Add(wxT("--subitem**Bigint"));

		if(columnType==dt_boolean)		//11
			strings.Add(wxT("--subitem--checked**Boolean"));
		else
			strings.Add(wxT("--subitem**Boolean"));

		if(columnType==dt_integer)		//12
			strings.Add(wxT("--subitem--checked**Integer"));
		else
			strings.Add(wxT("--subitem**Integer"));

		if(columnType==dt_money)		//13
			strings.Add(wxT("--subitem--checked**Money"));
		else
			strings.Add(wxT("--subitem**Money"));

		if(columnType==dt_varchar)		//14
			strings.Add(wxT("--subitem--checked**Varchar(1)"));   
		else
			strings.Add(wxT("--subitem**Varchar(1)"));   

		strings.Add(wxT("--subitem**Choose another datatype"));   //15
	
		strings.Add(wxT("--separator--")); 
		strings.Add(wxT("Primary Key Constraint name..."));  //17
		strings.Add(wxT("Unique Constraint name..."));  //18
		strings.Add(wxT("--separator--")); 
		strings.Add(wxT("Delete Table..."));  //20
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

ddDataType ddTextColumnFigure::getDataType()
{
	return columnType;
}

void ddTextColumnFigure::setDataType(ddDataType type)
{
	columnType=type;
}