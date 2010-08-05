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

#ifndef DDABSTRACTMENUFIGURE_H
#define DDABSTRACTMENUFIGURE_H
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/figures/ddAbstractFigure.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/utilities/ddCollection.h"



// Create Array Objects used as base for gqbCollections
class ddAbstractMenuFigure : public ddAbstractFigure
{
public:
	ddAbstractMenuFigure();
    ~ddAbstractMenuFigure();
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	virtual wxArrayString& popupStrings();
	virtual void setPopupStrings(wxArrayString& values);
	virtual void enablePopUp();
	virtual void disablePopUp();
	virtual bool menuEnabled();
	virtual void OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view);
protected:
	wxArrayString strings;
	bool showMenu;
private:

};
#endif
