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

#ifndef DDSIMPLETEXTTOOL_H
#define DDSIMPLETEXTTOOL_H

#include "dd/draw/tools/ddFigureTool.h"


class ddSimpleTextTool : public ddFigureTool
{

public:
	ddSimpleTextTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddSimpleTextTool();
	virtual void mouseDown(wxMouseEvent& event);  //Mouse Right Click
	virtual void activate();
	virtual void deactivate();
	virtual void mouseDrag(wxMouseEvent& event);
	virtual void changeHandler(wxCommandEvent& event);
protected:
private:
	void calculateSizeEntry();
	bool showEdit;
	wxTextCtrl *edit;
/*
	void setDefaultTool(ddITool *dt);
	ddITool* getDefaultTool();
	void setFigure(ddIFigure *fig);
	ddIFigure* getFigure();

	virtual void mouseUp(wxMouseEvent& event);


	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
protected:
	ddITool *defaultTool;
	ddIFigure *figure;
private:
	*/

};
#endif
