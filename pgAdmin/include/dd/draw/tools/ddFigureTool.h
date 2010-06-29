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

#ifndef DDFIGURETOOL_H
#define DDFIGURETOOL_H

#include "dd/draw/tools/ddAbstractTool.h"


class ddFigureTool : public ddAbstractTool
{
public:
	ddFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddFigureTool();
	void setDefaultTool(ddITool *dt);
	ddITool* getDefaultTool();
	void setFigure(ddIFigure *fig);
	ddIFigure* getFigure();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseMove(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
protected:
	ddITool *defaultTool;
	ddIFigure *figure;
private:
};
#endif
