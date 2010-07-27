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
#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/draw/tools/ddSimpleTextTool.h"
#include "dd/draw/utilities/ddGeometry.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddSimpleTextFigure::ddSimpleTextFigure(wxString textString)
{
	textEditable = false;
	font = settings->GetSystemFont();
	textForeground = *wxBLACK;
	textBackground = *wxTRANSPARENT_BRUSH;
	padding = 2;
	setText(textString);
	showMenu = false;
}

ddSimpleTextFigure::~ddSimpleTextFigure()
{
}

void ddSimpleTextFigure::setText(wxString textString)
{
	text = textString;
	recalculateDisplayBox();
}

//extended is flag that inform about returning an extended version of text stored at figure
wxString& ddSimpleTextFigure::getText(bool extended)
{
	return text;
}

void ddSimpleTextFigure::setFont(wxFont textFont)
{
	font = textFont;
	recalculateDisplayBox();
}

void ddSimpleTextFigure::setForeground(wxColour colour)
{
	textForeground = colour;
}

void ddSimpleTextFigure::setBackground(wxBrush background)
{
	textBackground = background;
}

void ddSimpleTextFigure::getFontMetrics(int &width, int &height)
{
	wxMemoryDC temp_dc;
	temp_dc.SetFont(font);
	temp_dc.SetTextForeground(textForeground);
	temp_dc.SetBrush(textBackground);
	if(getText(true).length()>5)
		temp_dc.GetTextExtent(getText(true),&width,&height);
	else
		temp_dc.GetTextExtent(wxT("EMPTY"),&width,&height);
}

void ddSimpleTextFigure::recalculateDisplayBox()
{
	int w,h;
	
	getFontMetrics(w,h);

	ddGeometry g;
	displayBox().width = g.max(w,10)+padding;
	displayBox().height = g.max(h,10)+padding;
}

void ddSimpleTextFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	setupLayout(context);
	context.DrawText(getText(true),copy.GetPosition());
}

void ddSimpleTextFigure::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	basicDraw(context,view);
}

void ddSimpleTextFigure::setupLayout(wxBufferedDC& context)
{
	context.SetFont(font);
	context.SetTextForeground(textForeground);
	context.SetBrush(textBackground);
}

//DD-TODO: Add event onTextChanged

void ddSimpleTextFigure::basicMoveBy(int x, int y)
{
	displayBox().x += x;
	displayBox().y += y;
}

ddITool* ddSimpleTextFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return textEditable ? new ddSimpleTextTool(editor,this,defaultTool) : defaultTool;
}

void ddSimpleTextFigure::setEditable(bool value)
{
	textEditable = value;
}

bool ddSimpleTextFigure::getEditable()
{
	return textEditable;
}

int ddSimpleTextFigure::getPadding()
{
	return padding;
}

wxArrayString& ddSimpleTextFigure::popupStrings()
{
	if(strings.Count()<=0)
	{
		strings.Clear();
		strings.Add(wxT("MENU"));
	}
	return strings;
};

void ddSimpleTextFigure::setPopupStrings(wxArrayString& values)
{
	strings = values;
}

void ddSimpleTextFigure::enablePopUp()
{
	showMenu = true;
}

void ddSimpleTextFigure::disablePopUp()
{
	showMenu = false;
}

bool ddSimpleTextFigure::menuEnabled()
{
	return 	showMenu;
}

void ddSimpleTextFigure::OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view)
{
	setText(strings[event.GetId()]);
}