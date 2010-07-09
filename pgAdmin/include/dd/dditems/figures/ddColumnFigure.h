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

#ifndef DDCOLUMNFIGURE_H
#define DDCOLUMNFIGURE_H


#include <wx/arrstr.h>

#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/dditems/utilities/ddDataType.h"

class ddTableFigure;

class ddColumnFigure : public ddSimpleTextFigure
{
public:
	ddColumnFigure(wxString& columnName, ddDataType dataType);
    ~ddColumnFigure();
	virtual wxString& getText(bool extended = false);
	virtual wxArrayString& popupStrings();
	virtual void OnTextPopupClick(wxCommandEvent& event);
	virtual void setText(wxString textString);
	virtual ddTableFigure* getOwnerTable();
	virtual void setOwnerTable(ddTableFigure *table);
	virtual void setShowDataType(bool value);
	ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	int getTextWidth();
	int getTextHeight();
protected:
	ddTableFigure *ownerTable;
private:
	ddDataType columnType;
	wxString out;
	bool showDataType;
};
#endif
