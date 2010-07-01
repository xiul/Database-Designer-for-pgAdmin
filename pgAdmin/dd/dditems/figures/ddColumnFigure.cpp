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
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/draw/main/ddDrawingView.h"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks

ddColumnFigure::ddColumnFigure(wxString& columnName, ddDataType dataType):
ddSimpleTextFigure(columnName)
{
	columnType = dataType;
	enablePopUp();
}



ddColumnFigure::~ddColumnFigure()
{

}

wxString& ddColumnFigure::getText(bool extended)
{
	if(extended)
	{
		wxString ddType = popupStrings()[columnType];
		out = wxString( ddSimpleTextFigure::getText() + wxString(wxT(" : ")) + ddType );
		return  out;
	}
	else
	{
		return ddSimpleTextFigure::getText();
	}
}

//event ID must match enum ddDataType!!! this event was created on view
void ddColumnFigure::OnTextPopupClick(wxCommandEvent& event)
{
	//DD-TODO: improve this
	switch(event.GetId())
	{
		case 0:
			columnType = dt_bigint;
		break;
		case 1:
			columnType = dt_boolean;
		break;
		case 2:
			columnType = dt_bool;
		break;
		case 3:
			columnType = dt_integer;
		break;
		case 4:
			columnType = dt_money;
		break;
		case 5:
			columnType = dt_varchar_n;
		break;
	}		
}

//must match enum ddDataType!!!
wxArrayString& ddColumnFigure::popupStrings()
{
	strings.Clear();
	strings.Add(wxT("BIGINT"));
	strings.Add(wxT("BOOLEAN"));
	strings.Add(wxT("INTEGER"));
	strings.Add(wxT("MONEY"));
	strings.Add(wxT("VARCHAR("));
	return strings;
};

/*
ddITool* ddColumnFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return textEditable ? new ddSimpleTextTool(editor,this,defaultTool) : defaultTool;
}
*/

/*
void ddColumnFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	if(refreshDisplayBox)
		recalculateDisplayBox(context);
	
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);

	setupLayout(context);

	context.DrawRectangle(copy); 
	context.DrawText(getText(true),copy.GetPosition());
}

/*
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

void ddSimpleTextFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	if(refreshDisplayBox)
		recalculateDisplayBox(context);
	
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);

	setupLayout(context);

	context.DrawRectangle(copy); 
	context.DrawText(text,copy.GetPosition());
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

*/