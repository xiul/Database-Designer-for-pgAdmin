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


ddColumnKindIcon::ddColumnKindIcon(){
	colType = none;
	icon = wxBitmap(ddprimarykey_xpm);  //initialize with any image for calculate goals
	iconToDraw = NULL;
	getBasicDisplayBox().SetSize(wxSize(getWidth(),getHeight()));
}

ddColumnKindIcon::~ddColumnKindIcon(){

}


wxArrayString& ddColumnKindIcon::popupStrings()
{
	if(strings.Count()<=0)
	{
		strings.Clear();
		strings.Add(wxT("None"));
		strings.Add(wxT("Primary Key"));
		strings.Add(wxT("Unique Key"));
		strings.Add(wxT("f Key"));
		strings.Add(wxT("fp Key"));
	}
	return strings;
};

void ddColumnKindIcon::OnTextPopupClick(wxCommandEvent& event)
{
	//strings[event.GetId()]
	changeIcon((ddColumnType)event.GetId());
}

void ddColumnKindIcon::changeIcon(ddColumnType type)
{
	colType=type;
	switch(type)
	{
		case 1:	icon = wxBitmap(ddprimarykey_xpm);
				break;
		case 2:	icon = wxBitmap(ddunique_xpm);
				break;
		case 3:	icon = wxBitmap(ddforeignkey_xpm);
				break;
		case 4:	icon = wxBitmap(ddprimaryforeignkey_xpm);  //DD-TODO: create this icon, test for fk pk
				break;
	}
	
	if(type!=none)
		iconToDraw = &icon;
	else
		iconToDraw = NULL;
	getBasicDisplayBox().SetSize(wxSize(getWidth(),getHeight()));
}

void ddColumnKindIcon::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	if(iconToDraw)
	{
		ddRect copy = displayBox();
		view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
		context.DrawBitmap(*iconToDraw,copy.GetPosition(),true);
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