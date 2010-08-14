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
	disconnectedEndTable = NULL;
}

ddRelationshipFigure::ddRelationshipFigure(ddIFigure *figure1, ddIFigure *figure2):
ddLineConnection(figure1,figure2)
{
}

ddRelationshipFigure::~ddRelationshipFigure()
{
	columnsHashMap::iterator it;
	ddRelationshipItem *item;
	for( it = chm.begin(); it != chm.end(); ++it )
	{
		wxString key = it->first;
		item = it->second;
		delete item;
	}
	chm.clear();
}

//DD-TODO: this function is execute two times at least each time because observers store in & out foreign key, fix this behavior
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
				bool NotFound = it == chm.end(); // will be true if not found

				if( col->isPrimaryKey() && NotFound )
				{
					NewFkColumn = new ddRelationshipItem(col,endTable, (fkMandatory?notnull:null), (fkIdentifying?pk:fk) );
					chm[col->getColumnName()]=NewFkColumn; //key will be original table name always
					endTable->addColumn(NewFkColumn->fkColumn);
					//hack to update relationship position when table size change
					endTable->moveBy(-1,0);
					endTable->moveBy(1,0);
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
							ddTableFigure *tmpTable=NewFkColumn->destinationTable;
							NewFkColumn->destinationTable->removeColumn(NewFkColumn->fkColumn);
							chm.erase(it);
							delete NewFkColumn;
							repeat=true;
							//hack to update relationship position when table size change
							tmpTable->moveBy(-1,0);
							tmpTable->moveBy(1,0);
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
		delete iterator;
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
				setOptionAtForeignKeys(notnull);
			}
			else
			{
				fkIdentifying=false;
				setLinePen(wxPen(*wxBLACK,1,wxSHORT_DASH));		
				setOptionAtForeignKeys(null);
			}
			break;
		case 4:
			fkMandatory = true;
			setLinePen(wxPen(*wxBLACK_PEN));
			fkIdentifying=!fkIdentifying;
			fkOneToMany = true;
			if(fkIdentifying)
			{
				setKindAtForeignKeys(pk);
			}
			else
			{
				setKindAtForeignKeys(fk);
			}
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

void ddRelationshipFigure::connectEnd(ddIConnector *end)
{
	ddLineConnection::connectEnd(end);
	if(getEndFigure() && getStartFigure())
		updateForeignKey();
}

void ddRelationshipFigure::connectStart(ddIConnector *start)
{
	ddLineConnection::connectStart(start);
	if(getEndFigure() && getStartFigure())
		updateForeignKey();
}

void ddRelationshipFigure::disconnectStart()
{
	disconnectedEndTable = (ddTableFigure*) getEndFigure();
	removeForeignKeys();
	ddLineConnection::disconnectStart();
}

void ddRelationshipFigure::disconnectEnd()
{
	disconnectedEndTable = (ddTableFigure*) getEndFigure();
	ddLineConnection::disconnectEnd();
	removeForeignKeys();

}

void ddRelationshipFigure::removeForeignKeys()
{
	if(disconnectedEndTable)
	{
		columnsHashMap::iterator it;
		ddRelationshipItem *NewFkColumn;

		//Hack to repeat for every time a column is elimite because hashmap is modified inside a for and now is invalid that for loop
		bool repeat;   
		do{
		repeat=false;
			for( it = chm.begin(); it != chm.end(); ++it )
			{
				wxString key = it->first;
				NewFkColumn = it->second;
				if(NewFkColumn->destinationTable->includes(NewFkColumn->fkColumn) )
				{
					NewFkColumn->destinationTable->removeColumn(NewFkColumn->fkColumn);
					chm.erase(it);
					delete NewFkColumn;
					repeat = true;
					break;
				}
			}
		}while(repeat);
		chm.clear();
		disconnectedEndTable=NULL;
	}
}

void ddRelationshipFigure::setOptionAtForeignKeys(ddColumnOptionType type)
{
	columnsHashMap::iterator it;
	ddRelationshipItem *item;
	for( it = chm.begin(); it != chm.end(); ++it )
	{
		wxString key = it->first;
		item = it->second;
		item->fkColumn->setColumnOption(type);
	}
}

void ddRelationshipFigure::setKindAtForeignKeys(ddColumnType type)
{
	columnsHashMap::iterator it;
	ddRelationshipItem *item;
	for( it = chm.begin(); it != chm.end(); ++it )
	{
		wxString key = it->first;
		item = it->second;
		item->fkColumn->setColumnKind(type);
	}
	if(type==pk || type==fk) //set as identifying relationship (hierarchy)
	{
		ddTableFigure *table = (ddTableFigure*) getEndFigure();
		table->updateFkObservers();
	}
}
wxString ddRelationshipFigure::generateSQL()
{
	wxString tmp(wxT("FOREIGN KEY ( "));
	columnsHashMap::iterator it;
	ddRelationshipItem *item;
	for( it = chm.begin(); it != chm.end(); ++it )
	{
		wxString key = it->first;
		item = it->second;
		tmp += item->fkColumn->getColumnName();
		
		if(it!=chm.end())
		{
			tmp+=wxT(" , ");
		}
		else
		{
			tmp+=wxT(" )");
		}
	}	
	
	tmp += wxT("REFERENCES ") + ((ddTableFigure*)getStartFigure())->getTableName() + wxT(" ( ");
	for( it = chm.begin(); it != chm.end(); ++it )
	{
		wxString key = it->first;
		item = it->second;
		tmp += item->original->getColumnName();
		
		if(it!=chm.end())
		{
			tmp+=wxT(" , ");
		}
		else
		{
			tmp+=wxT(" )");
		}
	}

	return tmp;
}

/*
bool ddRelationshipFigure::belongsToThisTable(ddTableFigure *possibleOwner)
{
	return possibleOwner == getStartFigure();
}

/*
//Normal behavior is each figure observe to other (start->end,end->start) but here only need (start->end), reverse is a dependentFigure
//Observer kind = ddRelationshipFigure  DependentFigure kind = ddRelationshipFigure
void ddRelationshipFigure::connectFigure (ddIConnector *connector)
{
	if(getStartConnector()==connector)
	{
		ddLineConnection::connectFigure(connector);
	}
	else if(connector)
	{
		ddTableFigure *t = (ddTableFigure*)connector->getOwner();
		t->addDependentRelationship(this);
	}
}

void ddRelationshipFigure::disconnectFigure (ddIConnector *connector)
{
	if(getStartConnector()==connector)
	{
		ddLineConnection::disconnectFigure(connector);
	}
	else if(connector)
	{
			ddTableFigure *t = (ddTableFigure*)connector->getOwner();
			t->removeDependentRelationship(this);
	}
}

*/


/************************
Items at hash map table
*************************/

ddRelationshipItem::ddRelationshipItem(ddColumnFigure *originalColumn, ddTableFigure *destination, ddColumnOptionType type, ddColumnType colType)
{
	original = originalColumn;
	destinationTable = destination;
	wxString newName = originalColumn->getOwnerTable()->getTableName();
	newName.append(wxT("_"));
	newName.append(originalColumn->getColumnName(false));
	//DD-TODO: improve fk name
	fkColumn = new ddColumnFigure(newName,destinationTable,this);
	fkColumn->setColumnOption(type);
	fkColumn->setColumnKind(colType);
}

ddRelationshipItem::~ddRelationshipItem()
{
/*	if(fkColumn)
		delete fkColumn;*/
}

