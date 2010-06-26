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

#ifndef DDCOMPOSITEFIGURETOOL_H
#define DDCOMPOSITEFIGURETOOL_H

#include "dd/draw/tools/ddFigureTool.h"


class ddCompositeFigureTool : public ddFigureTool
{
public:
	ddCompositeFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddCompositeFigureTool();
	void setDefaultTool(ddITool *dt);
	ddITool* getDefaultTool();
	virtual void mouseDown(wxMouseEvent& event);  //Mouse Right Click
	virtual void activate();
	virtual void deactivate();
	void setDelegateTool(ddITool *tool);
	ddITool* getDelegateTool();

/*
	void setFigure(ddIFigure *fig);
	ddIFigure* getFigure();
	
	virtual void mouseUp(wxMouseEvent& event);
	virtual void mouseMove(wxMouseEvent& event);
	virtual void mouseDrag(wxMouseEvent& event);
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
protected:
	ddITool *defaultTool;
	ddIFigure *figure;
private:
*/
};
#endif
