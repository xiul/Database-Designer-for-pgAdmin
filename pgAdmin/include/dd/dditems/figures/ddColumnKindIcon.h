//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbObject.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbObject.h - 
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCOLUMNKINDICON_H
#define DDCOLUMNKINDICON_H

#include "dd/draw/figures/ddAbstractMenuFigure.h"

//#include "dd/draw/utilities/ddRect.h"
/*
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/utilities/ddCollection.h"*/



// Create Array Objects used as base for gqbCollections
class ddColumnKindIcon : public ddAbstractMenuFigure
{
public:
	ddColumnKindIcon();
    ~ddColumnKindIcon();
	virtual wxArrayString& popupStrings();
	virtual void OnTextPopupClick(wxCommandEvent& event);
	virtual void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);		
	//virtual void changeBitmap(wxBitmap *image);
	virtual int getWidth();
	virtual int getHeight();

protected:

private:
	wxBitmap *iconToDraw;
	wxBitmap icon;
};
#endif
