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

#ifndef DDCOLUMNFIGURETOOL_H
#define DDCOLUMNFIGURETOOL_H

#include "dd/draw/tools/ddFigureTool.h"


class ddColumnFigureTool : public ddFigureTool
{
public:
	ddColumnFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddColumnFigureTool();
	virtual void setDefaultTool(ddITool *dt);
	virtual ddITool* getDefaultTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void activate();
	virtual void deactivate();
	virtual void setDelegateTool(ddITool *tool);
	virtual ddITool* getDelegateTool();
protected:
	ddITool *delegateTool;
private:


/*
	void setFigure(ddIFigure *fig);
	ddIFigure* getFigure();
	
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseMove(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);

*/
};
#endif
