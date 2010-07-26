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

#ifndef DDCOLUMNOPTIONICON_H
#define DDCOLUMNOPTIONICON_H

#include "dd/draw/figures/ddAbstractMenuFigure.h"



const enum ddColumnOptionType {
	null=0,
	notnull
};


class ddColumnOptionIcon : public ddAbstractMenuFigure
{
public:
	ddColumnOptionIcon();
    ~ddColumnOptionIcon();
	virtual wxArrayString& popupStrings();
	virtual void OnTextPopupClick(wxCommandEvent& event);
	virtual void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);		
	virtual void changeIcon(ddColumnOptionType type);
	virtual int getWidth();
	virtual int getHeight();
	ddColumnOptionType getOption();

protected:

private:
	ddColumnOptionType colOption;
	wxBitmap *iconToDraw;
	wxBitmap icon;
};
#endif
