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

#ifndef DDIFIGURE_H
#define DDIFIGURE_H
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/main/ddObject.h"
#include "dd/draw/utilities/ddCollection.h"
#include "dd/draw/handles/ddIHandle.h"


class ddITool;			// HACK-FIX circular reference
class ddDrawingEditor;

// Create Array Objects used as base for gqbCollections
class ddIFigure : public ddObject
{
public:
	ddIFigure();
    ~ddIFigure();

	virtual ddRect& displayBox();
	virtual ddRect& getBasicDisplayBox();
	virtual void draw (wxBufferedDC& context);
	virtual void drawSelected (wxBufferedDC& context);
	virtual ddCollection* handlesEnumerator();
	virtual void addDependentFigure (ddIFigure *figure);
	virtual void removeDependentFigure (ddIFigure *figure);
	virtual void addHandle (ddIHandle *handle);
	virtual void removeHandle (ddIHandle *handle);
	virtual void moveBy(int x, int y);
	virtual void moveTo(int x, int y);
	virtual bool containsPoint(int x, int y);
	virtual bool isSelected();
	virtual void setSelected(bool value);
	
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);

protected:
	ddRect basicDisplayBox;
	ddCollection *figures;
	ddCollection *handles;
	ddCollection *dependentFigures;
private:
	bool selected;
};
#endif
