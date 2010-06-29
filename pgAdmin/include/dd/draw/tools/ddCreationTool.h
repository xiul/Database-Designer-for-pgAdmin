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

#ifndef DDCREATIONTOOL_H
#define DDCREATIONTOOL_H

#include "dd/draw/tools/ddAbstractTool.h"
#include "dd/draw/figures/ddIFigure.h"


class ddCreationTool : public ddAbstractTool
{
public:
	ddCreationTool(ddDrawingEditor *editor, ddIFigure *prototype);
    ~ddCreationTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void activate();
	virtual void deactivate();
	virtual void setPrototype(ddIFigure *prototype);
	virtual ddIFigure* getPrototype();
	//DD-TODO: add this virtual IDrawingEditor editor and undoactivity

protected:
	ddIFigure *figurePrototype;


};
#endif
