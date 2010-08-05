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

class ddColumnFigure;

const enum ddColumnType {
	pk=0,
	uk,
	fk,
	pkfk,
	pkuk,
	none
};


class ddColumnKindIcon : public ddAbstractMenuFigure
{
public:
	ddColumnKindIcon(ddColumnFigure *owner);
    ~ddColumnKindIcon();
	virtual wxArrayString& popupStrings();
	virtual void OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view);
	virtual void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);		
	virtual void changeIcon(ddColumnType type, ddDrawingView *view=NULL, bool interaction=true);
	virtual int getWidth();
	virtual int getHeight();
	ddColumnType getKind();
	ddColumnFigure* getOwnerColumn();
	virtual int getUniqueConstraintIndex();
	virtual void setUniqueConstraintIndex(int i);
	

protected:

private:
	ddColumnFigure *ownerColumn;
	ddColumnType colType;
	wxBitmap *iconToDraw;
	wxBitmap icon;
	int ukIndex;

	//multiple Uk management at table
	void syncUkIndexes();
	void uniqueConstraintManager(bool ukCol, ddDrawingView *view=NULL, bool interaction=true);
};
#endif
