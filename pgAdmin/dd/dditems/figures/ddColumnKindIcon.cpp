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
#include <wx/pen.h>

// App headers
#include "dd/dditems/figures/ddColumnKindIcon.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/figures/ddTableFigure.h"

//Images
#include "images/ddforeignkey.xpm"
#include "images/ddprimarykey.xpm"
#include "images/ddunique.xpm"
#include "images/ddprimaryforeignkey.xpm"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddColumnKindIcon::ddColumnKindIcon(ddColumnFigure *owner){
	ownerColumn=owner;
	colType = none;
	icon = wxBitmap(ddprimarykey_xpm);  //initialize with any image for calculate goals
	iconToDraw = NULL;
	getBasicDisplayBox().SetSize(wxSize(getWidth(),getHeight()));
	ukIndex=-1;
}

ddColumnKindIcon::~ddColumnKindIcon(){

}


wxArrayString& ddColumnKindIcon::popupStrings()
{
	strings.Clear();
/*	if(colType==none)
		strings.Add(wxT("--checked**None"));
	else
		strings.Add(wxT("None"));
*/	
	if(colType==pk)
		strings.Add(wxT("--checked**Primary Key"));   //DD-TODO: primary key then put not null at same time
	else
		strings.Add(wxT("Primary Key"));
	
	if(colType==uk)
		strings.Add(wxT("--checked**Unique Key..."));
	else
		strings.Add(wxT("Unique Key"));
	return strings;
};

void ddColumnKindIcon::OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	//strings[event.GetId()]
	changeIcon((ddColumnType)event.GetId(),view);
}

ddColumnFigure* ddColumnKindIcon::getOwnerColumn()
{
	return ownerColumn;
}

void ddColumnKindIcon::changeIcon(ddColumnType type, ddDrawingView *view, bool interaction) 
{
	bool ukCol = colType==uk;
	
	//colType=type;

	wxString tmpString;
	switch(type)
	{
		case 0:	icon = wxBitmap(ddprimarykey_xpm);
				if(colType==pk){
					colType=none;
				}
				else
				{
					if(colType==uk)
					{
						syncUkIndexes();
						ukIndex=-1;
					}
					colType=pk;
				}
				break;
		case 1: uniqueConstraintManager(ukCol,view,interaction);
				icon = wxBitmap(ddunique_xpm);
				break;
		case 2:	icon = wxBitmap(ddforeignkey_xpm);
				colType=fk;
				break;
		case 3:	icon = wxBitmap(ddprimaryforeignkey_xpm);
				colType=pkfk;
				break;
	}
	
	if(colType!=none)
		iconToDraw = &icon;
	else
	{
		iconToDraw = NULL;
		ukIndex=-1;
	}
	getBasicDisplayBox().SetSize(wxSize(getWidth(),getHeight()));
}

void ddColumnKindIcon::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	if(iconToDraw)
	{
		ddRect copy = displayBox();
		view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
		context.DrawBitmap(*iconToDraw,copy.GetPosition(),true);
		//DD-TODO: improve this number
		if(colType==uk && ukIndex>0)
		{
			wxFont font = settings->GetSystemFont();
			font.SetPointSize(6);
			context.SetFont(font);
			wxString inumber = wxString::Format(wxT("%d"), (int)ukIndex+1);
			context.DrawText(inumber,copy.x+4,copy.y+2);
		}
	}
}

void ddColumnKindIcon::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	basicDraw(context,view);
}

int ddColumnKindIcon::getWidth()
{
	if(iconToDraw)
		return iconToDraw->GetWidth();
	else
		return 8;
}

int ddColumnKindIcon::getHeight()
{
	if(iconToDraw)
		return iconToDraw->GetHeight();
	else
		return 10;
}

ddColumnType ddColumnKindIcon::getKind()
{
	return colType;
}

int ddColumnKindIcon::getUniqueConstraintIndex()
{
	return ukIndex;
}

void ddColumnKindIcon::setUniqueConstraintIndex(int i)
{
	ukIndex=i;
}

void ddColumnKindIcon::uniqueConstraintManager(bool ukCol, ddDrawingView *view, bool interaction)
{
  wxString tmpString;
  colType=uk;
  if(ukCol)
  {
	syncUkIndexes();
	getOwnerColumn()->setUniqueConstraintIndex(-1);
	colType=none;
	//getOwnerColumn()->setColumnKind(none);

  }else //colType!=uk
  {
	if(interaction)
	{
		if(ownerColumn->getOwnerTable()->getUkConstraintsNames().Count()==0)   //DD-TODO: solve problem of charging values without user interaction (save/load)
		{
			tmpString = getOwnerColumn()->getOwnerTable()->getTableName();
			tmpString.append(wxT("_uk"));
			tmpString=wxGetTextFromUser(wxT("Name of new Unique Key constraint:"),tmpString,tmpString,view);
			if(tmpString.length()>0)
			{
				getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Add(tmpString);						
				ukIndex=0;
			}
			else
			{
				colType=none;
				ukIndex=-1;
			}
		}
		else  //>0
		{
			getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Add(wxString(wxT("Add new Unique Constraint...")));
			int i = wxGetSingleChoiceIndex(wxT("Select Unique Key to add Column"),wxT("Select Unique Key to add Column:"),getOwnerColumn()->getOwnerTable()->getUkConstraintsNames(),view);
			getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().RemoveAt(getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Count()-1);
			if(i>=0)
			{
				if(i==getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Count())
				{
					tmpString = getOwnerColumn()->getOwnerTable()->getTableName();
					tmpString.append(wxT("_uk"));
					
					int newIndex=i+1;
					wxString inumber = wxString::Format(wxT("%s%d"), tmpString.c_str(),(int)newIndex);
					//Validate new name of uk doesn't exists
					while(getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Index(inumber,false)!=-1){
						newIndex++;
						inumber = wxString::Format(wxT("%s%d"), tmpString.c_str(),(int)newIndex);
					}
					inumber = wxString::Format(wxT("%d"), (int)newIndex);
					tmpString.append(inumber);
					tmpString=wxGetTextFromUser(wxT("Name of new Unique Key constraint:"),tmpString,tmpString,view);
					if(tmpString.length()>0)
					{
						getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().Add(tmpString);						
						ukIndex=i;
					}
					else
					{
						colType=none;
						ukIndex=-1;
					}
				}
				else
				{
					ukIndex=i;
				}
			}
			else
			{
				colType=none;
				ukIndex=-1;
			}
		}
	}
  }
}

void ddColumnKindIcon::syncUkIndexes()
{
	ddColumnFigure *col;
	bool lastUk=true;
	int maxIndex=-1;
	ddIteratorBase *iterator = getOwnerColumn()->getOwnerTable()->figuresEnumerator();
		iterator->Next(); //First Figure is Main Rect
		iterator->Next(); //Second Figure is Table Title
		while(iterator->HasNext())
		{
			col = (ddColumnFigure*) iterator->Next();
			
			if(col->getUniqueConstraintIndex() >  maxIndex)
				maxIndex = col->getUniqueConstraintIndex();

			if(col!=getOwnerColumn() && (col->getUniqueConstraintIndex() == getOwnerColumn()->getUniqueConstraintIndex()))
				lastUk=false;
		}
	if(lastUk)
	{
		//fix uks indexes
		iterator->ResetIterator();
		iterator->Next(); //First Figure is Main Rect
		iterator->Next(); //Second Figure is Table Title
		while(iterator->HasNext())
		{
			col = (ddColumnFigure*) iterator->Next();
			if( col->getUniqueConstraintIndex() > getOwnerColumn()->getUniqueConstraintIndex() ) 
				col->setUniqueConstraintIndex(col->getUniqueConstraintIndex()-1);
		}
		getOwnerColumn()->getOwnerTable()->getUkConstraintsNames().RemoveAt(getOwnerColumn()->getUniqueConstraintIndex());
		getOwnerColumn()->setUniqueConstraintIndex(-1);
	}
	delete iterator;
}