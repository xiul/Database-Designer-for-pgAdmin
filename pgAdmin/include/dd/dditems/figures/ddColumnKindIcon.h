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


const enum ddColumnType {
	none=0,
	pk,
	fk,
	uk,
	pkfk
};


class ddColumnKindIcon : public ddAbstractMenuFigure
{
public:
	ddColumnKindIcon();
    ~ddColumnKindIcon();
	virtual wxArrayString& popupStrings();
	virtual void OnTextPopupClick(wxCommandEvent& event);
	virtual void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);		
	virtual void changeIcon(ddColumnType type);
	virtual int getWidth();
	virtual int getHeight();
	ddColumnType getKind();

protected:

private:
	ddColumnType colType;
	wxBitmap *iconToDraw;
	wxBitmap icon;
};
#endif
