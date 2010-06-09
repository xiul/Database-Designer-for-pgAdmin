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

// App headers
#include "dd/draw/locators/ddPolyLineLocator.h"
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/figures/ddPolyLineFigure.h"

ddPolyLineLocator::~ddPolyLineLocator(){
}

ddPolyLineLocator::ddPolyLineLocator(int index){
	indx=index;
}

ddPoint* ddPolyLineLocator::locate(ddIFigure *owner){
	if(owner)
	{
		ddPolyLineFigure *figure = (ddPolyLineFigure *) owner;
		return figure->pointAt(indx);
	}
	else
	{
		return new ddPoint();
	}
}
