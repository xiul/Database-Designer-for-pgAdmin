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
#include "images/foreignkey.xpm"
#include "images/primarykey.xpm"
#include "images/unique.xpm"
#include "images/parser.xpm"  //test for fk pk


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddColumnKindIcon::ddColumnKindIcon(){
	 icon = wxBitmap(primarykey_xpm);
	 iconToDraw = &icon;
}

ddColumnKindIcon::~ddColumnKindIcon(){

}


wxArrayString& ddColumnKindIcon::popupStrings()
{
	if(strings.Count()<=0)
	{
		strings.Clear();
		strings.Add(wxT("Primary Key"));
		strings.Add(wxT("Foreign Key"));
		strings.Add(wxT("Unique Key"));
		strings.Add(wxT("Primary Foreing Key"));
	}
	return strings;
};

void ddColumnKindIcon::OnTextPopupClick(wxCommandEvent& event)
{
	//Action on popup goes here
	//strings[event.GetId()]
	switch(event.GetId())
	{
		case 0:	icon = wxBitmap(primarykey_xpm);
				break;
		case 1:	icon = wxBitmap(foreignkey_xpm);
				break;
		case 2:	icon = wxBitmap(unique_xpm);
				break;
		case 3:	icon = wxBitmap(primarykey_xpm);
				break;
		case 4:	icon = wxBitmap(parser_xpm);
				break;
	}
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
		return 16;
}

int ddColumnKindIcon::getHeight()
{
	if(iconToDraw)
		return iconToDraw->GetHeight();
	else
		return 16;
}