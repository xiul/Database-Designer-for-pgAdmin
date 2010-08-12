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
#include <wx/dcbuffer.h>

// App headers
#include "dd/dditems/figures/ddRelationshipFigure.h"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddRelationshipFigure::ddRelationshipFigure():
ddLineConnection()
{
	fkFromPk = true;
	fkMandatory = true;
	fkOneToMany = true;
	fkIdentifying = false;
	ukIndex = -1;
}

ddRelationshipFigure::ddRelationshipFigure(ddIFigure *figure1, ddIFigure *figure2):
ddLineConnection(figure1,figure2)
{
}

ddRelationshipFigure::~ddRelationshipFigure()
{
	chm.clear();
}

/*
ddITool* ddRelationshipFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return new ddPolyLineFigureTool(editor,this,new ddMenuTool(editor,this,defaultTool));
}
*/



/*
ddITool* ddRelationshipFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return new ddMenuTool(editor,this,defaultTool);
}
*/

/*
void ddRelationshipFigure::addFkColumn(ddColumnFigure *column)
{
	chm[column->getColumnName(false)]=column;
}

void ddRelationshipFigure::removeFkColumn(wxString columnName)
{
	chm.erase(columnName);
}
*/
void ddRelationshipFigure::updateForeignKey()
{
	if(getEndFigure() && getStartFigure() && getStartFigure()->ms_classInfo.IsKindOf(&ddTableFigure::ms_classInfo) && getEndFigure()->ms_classInfo.IsKindOf(&ddTableFigure::ms_classInfo))
	{
		ddTableFigure *startTable = (ddTableFigure*) getStartFigure();
		ddTableFigure *endTable = (ddTableFigure*) getEndFigure();
		ddColumnFigure *col;
		ddRelationshipItem *NewFkColumn;

		ddIteratorBase *iterator = startTable->figuresEnumerator();
		iterator->Next(); //First Figure is Main Rect
		iterator->Next(); //Second Figure is Table Title
		while(iterator->HasNext())
		{
			col = (ddColumnFigure*) iterator->Next();
			if(fkFromPk)  //RELATIONSHIP KIND IS USING A PK (PRIMARY KEY) AS FOREIGN KEYS
			{
				//Add new pk columns from source fk table to destination
				columnsHashMap::iterator it = chm.find(col->getColumnName());
				bool NotFound = it == chm.end(); // will be true

				if( col->isPrimaryKey() && NotFound )
				{
					NewFkColumn = new ddRelationshipItem(col,endTable);
					chm[col->getColumnName()]=NewFkColumn; //key will be original table name always
					endTable->addColumn(NewFkColumn->fkColumn);
				}

				//Delete old Fk columns now not pk or deleted from source fk table.
				//DD-TODO: optimize this later  and add deletes when needed

				//Hack to repeat for every time a column is elimite because hashmap is modified inside a for and now is invalid that for loop
				bool repeat;   
				do{
					repeat=false;
					for( it = chm.begin(); it != chm.end(); ++it )
					{
						wxString key = it->first;
						NewFkColumn = it->second;
						if( !NewFkColumn->original->isPrimaryKey() || !startTable->includes(NewFkColumn->original) )
						{
							NewFkColumn->destinationTable->removeColumn(NewFkColumn->fkColumn);
							delete NewFkColumn;
							chm.erase(it);
							repeat=true;
						}
						if(repeat)
							break;
					}

				}while(repeat);

			}
			else   //RELATIONSHIP KIND IS USING A UK (UNIQUE KEY) AS FOREIGN KEYS
			{
				//DD-TODO: Add this functionality.
			}
		}
	}
	else 
	{
		wxMessageBox(wxT("Error invalid kind of start figure at relationship"),wxT("Error invalid kind of start figure at relationship"),wxICON_ERROR);
	}
}


wxArrayString& ddRelationshipFigure::popupStrings()
{
	strings.clear();
	
	if(fkFromPk)
	{
		strings.Add(wxT("--checked**Foreign Key from Primary Key"));  //0
		strings.Add(wxT("Foreign Key from Unique Key..."));   //1
	}
	else
	{
		strings.Add(wxT("Foreign Key from Primary Key"));   //0
		strings.Add(wxT("--checked**Foreign Key from Unique Key(Uk#)"));   //1
	}
	
	strings.Add(wxT("--separator--"));   //2
	
	if(fkMandatory)
	{
		strings.Add(wxT("--checked**Mandatory relationship kind"));   //3
		//strings.Add(wxT("Optional relationship kind"));   //4

	}
	else
	{
		strings.Add(wxT("Mandatory relationship kind"));   //3
		//strings.Add(wxT("--checked**Optional relationship kind"));   //4
	}
		
	if(fkIdentifying)
		strings.Add(wxT("--checked**Identifying relationship")); //4
	else
		strings.Add(wxT("Identifying relationship")); //4

	strings.Add(wxT("--separator--"));   //5

	if(fkOneToMany)
	{
		strings.Add(wxT("--checked**1:M"));   //6
		strings.Add(wxT("1:1"));   //7
	}
	else
	{
		strings.Add(wxT("1:M"));   //6
		strings.Add(wxT("--checked**1:1"));   //7
	}

return strings;
}


void ddRelationshipFigure::OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	switch(event.GetId())
	{
		case 0:
		case 1:
			//fkFromPk=!fkFromPk;
			wxMessageBox(wxT("To be implemente soon..."),wxT("To be implemente soon..."),wxICON_INFORMATION, (wxScrolledWindow*) view);
			break;
		case 3:
			fkMandatory=!fkMandatory;
			if(fkMandatory)
			{
				setLinePen(wxPen(*wxBLACK_PEN));
			}
			else
			{
				fkIdentifying=false;
				setLinePen(wxPen(*wxBLACK,1,wxSHORT_DASH));		
			}
			break;
		case 4:
			fkMandatory = true;
			setLinePen(wxPen(*wxBLACK_PEN));
			fkIdentifying=!fkIdentifying;
			fkOneToMany = true;
			break;
		case 6:
		case 7:
			fkOneToMany=!fkOneToMany;
			break;
	}
}

bool ddRelationshipFigure::getIdentifying()
{
	return fkIdentifying;
}

bool ddRelationshipFigure::getOneToMany()
{
	return fkOneToMany;
}

bool ddRelationshipFigure::getMandatory()
{
	return fkMandatory;
}


/*
void ddRelationshipFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	if(fkMandatory)
	{
		context.SetPen(wxPen(*wxBLACK_PEN));
	}
	else
	{
		context.SetPen(wxPen(*wxBLACK,1,wxSHORT_DASH));		
	}
	ddLineConnection::basicDraw(context,view);
}

void ddRelationshipFigure::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	if(fkMandatory)
	{
		context.SetPen(wxPen(*wxBLACK_PEN));
	}
	else
	{
		context.SetPen(wxPen(*wxBLACK,1,wxSHORT_DASH));		
	}
	ddLineConnection::basicDrawSelected(context,view);
}*/


/*
Items at hash map table
*/

ddRelationshipItem::ddRelationshipItem(ddColumnFigure *originalColumn, ddTableFigure *destination)
{
	original = originalColumn;
	destinationTable = destination;
	wxString newName = originalColumn->getOwnerTable()->getTableName();
	newName.append(wxT("_"));
	newName.append(originalColumn->getColumnName(false));
	//DD-TODO: improve fk name
	fkColumn = new ddColumnFigure(newName,destinationTable,true);
}

ddRelationshipItem::~ddRelationshipItem()
{
	/*	if(fkColumn)
		delete fkColumn;
		raise an error is delete by array
		*/
}
