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
#include "dd/draw/figures/ddAbstractFigure.h"
#include "dd/dditems/figures/ddColumnKindIcon.h"
#include "dd/dditems/figures/ddColumnOptionIcon.h"
#include "dd/dditems/figures/ddTextColumnFigure.h"

class ddTableFigure;

// This figure is like composite but minimize overhead for columns
class ddColumnFigure : public ddAbstractFigure
{
public:
	ddColumnFigure(wxString& columnName, ddTableFigure *owner);
    ~ddColumnFigure();
	virtual void basicMoveBy(int x, int y);
	virtual void moveTo(int x, int y);
	virtual bool containsPoint(int x, int y);
	virtual ddRect& getBasicDisplayBox();
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual void drawSelected(wxBufferedDC& context, ddDrawingView *view);
	virtual ddIFigure* findFigure(int x, int y);
	virtual ddIFigure* getFigureAt(int pos);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	virtual void sendToBack(ddIFigure *figure);
	virtual void sendToFront(ddIFigure *figure);
	virtual ddTableFigure* getOwnerTable();
	virtual void setOwnerTable(ddTableFigure *table);
	void displayBoxUpdate();
	bool isNull();
	bool isNotNull();
	bool isPrimaryKey();
	bool isUniqueKey();
	bool isPlain();
	void setColumnKind(ddColumnType type);
	void setColumnOption(ddColumnOptionType type);
protected:
	ddColumnKindIcon *leftImage;
	ddColumnOptionIcon *centerImage;
	ddTextColumnFigure *columnText;
	ddTableFigure *ownerTable;
private:
	
};
#endif
