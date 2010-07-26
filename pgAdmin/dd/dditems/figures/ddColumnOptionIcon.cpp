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
#include "dd/dditems/figures/ddColumnOptionIcon.h"
#include "dd/draw/main/ddDrawingView.h"

//Images
#include "images/ddnull.xpm"
#include "images/ddnotnull.xpm"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddColumnOptionIcon::ddColumnOptionIcon(){
	 colOption=null;
	 icon = wxBitmap(ddnull_xpm);
	 iconToDraw = &icon;
	 getBasicDisplayBox().SetSize(wxSize(getWidth(),getHeight()));
}

ddColumnOptionIcon::~ddColumnOptionIcon(){

}


wxArrayString& ddColumnOptionIcon::popupStrings()
{
	if(strings.Count()<=0)
	{
		strings.Clear();
		strings.Add(wxT("Null"));
		strings.Add(wxT("Not Null"));
	}
	return strings;
};

void ddColumnOptionIcon::OnTextPopupClick(wxCommandEvent& event)
{
	//strings[event.GetId()]
	changeIcon((ddColumnOptionType)event.GetId());
}

void ddColumnOptionIcon::changeIcon(ddColumnOptionType type)
{
	colOption=type;
	switch(type)
	{
		case 0:	icon = wxBitmap(ddnull_xpm);
				break;
		case 1:	icon = wxBitmap(ddnotnull_xpm);
				break;
	}
	getBasicDisplayBox().SetSize(wxSize(getWidth(),getHeight()));
}

void ddColumnOptionIcon::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	if(iconToDraw)
	{
		ddRect copy = displayBox();
		view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
		context.DrawBitmap(*iconToDraw,copy.GetPosition(),true);
	}
}

void ddColumnOptionIcon::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	basicDraw(context,view);
}

int ddColumnOptionIcon::getWidth()
{
	if(iconToDraw)
		return iconToDraw->GetWidth();
	else
		return 8;
}

int ddColumnOptionIcon::getHeight()
{
	if(iconToDraw)
		return iconToDraw->GetHeight();
	else
		return 10;
}

ddColumnOptionType ddColumnOptionIcon::getOption()
{
	return colOption;
}
