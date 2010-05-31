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

#ifndef DDSELECTIONTOOL_H
#define DDSELECTIONTOOL_H

#include "dd/draw/ddITool.h"
#include "dd/draw/ddAbstractTool.h"

class ddSelectionTool : public ddAbstractTool
{
public:
	ddSelectionTool(ddDrawingEditor *owner);
    ~ddSelectionTool();
	virtual void mouseDown(wxMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(wxMouseEvent& event);
	virtual void mouseMove(wxMouseEvent& event);
	virtual void mouseDrag(wxMouseEvent& event);
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
	void setDelegateTool(ddITool *tool);
	ddITool* getDelegateTool();

protected:
	ddITool *_delegateTool;
private:
	
	void deleteFigures(ddDrawingView *view);
};
#endif
