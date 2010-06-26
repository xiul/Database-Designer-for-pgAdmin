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
	text = textString;
	textEditable = false;
	font = settings->GetSystemFont();
	textForeground = *wxBLACK;
	textBackground = wxBrush (wxColour(245, 245, 245),wxSOLID);
	refreshDisplayBox = true;
	padding = 2;
}

ddSimpleTextFigure::~ddSimpleTextFigure()
{
}

void ddSimpleTextFigure::setText(wxString textString)
{
	text = textString;
	refreshDisplayBox = true;
	//DD-TODO: update displaybox size
}
wxString& ddSimpleTextFigure::getText()
{
	return text;
}

void ddSimpleTextFigure::setFont(wxFont textFont)
{
	font = textFont;
	refreshDisplayBox = true;
}

void ddSimpleTextFigure::setForeground(wxColour colour)
{
	textForeground = colour;
	refreshDisplayBox = true;
}

void ddSimpleTextFigure::setBackground(wxBrush background)
{
	textBackground = background;
	refreshDisplayBox = true;
}

void ddSimpleTextFigure::getFontMetrics(int &width, int &height, wxBufferedDC& context)
{
	context.SetFont(font);
	if(text.length()>5)
		context.GetTextExtent(text,&width,&height);
	else
		context.GetTextExtent(wxT("EMPTY"),&width,&height);
	//DD-TODO: avoid in a future twin function in DrawingView because tool hack
}



void ddSimpleTextFigure::recalculateDisplayBox(wxBufferedDC& context)
{
	int w,h;
	
	getFontMetrics(w,h,context);

	ddGeometry g;
	displayBox().width = g.max(w,10)+padding;
	displayBox().height= g.max(h,10)+padding;
	refreshDisplayBox = false;
	//DD-TODO: avoid in a future twin function in DrawingView because tool hack
}

void ddSimpleTextFigure::basicDraw(wxBufferedDC& context)
{
	if(refreshDisplayBox)
		recalculateDisplayBox(context);
	
	setupLayout(context);

	context.DrawRectangle(this->displayBox()); 
	context.DrawText(text,getBasicDisplayBox().GetPosition());
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

