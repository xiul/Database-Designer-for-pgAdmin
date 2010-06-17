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

#ifndef DDCONNECTIONCREATIONTOOL_H
#define DDCONNECTIONCREATIONTOOL_H

#include "dd/draw/tools/ddAbstractTool.h"
#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/figures/ddIConnectionFigure.h"

class ddConnectionCreationTool : public ddAbstractTool
{
public:
	ddConnectionCreationTool(ddDrawingEditor *editor, ddIConnectionFigure *figure);
    ~ddConnectionCreationTool();

	virtual void mouseDrag(wxMouseEvent& event);
	virtual void mouseDown(wxMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(wxMouseEvent& event);
	virtual void mouseMove(wxMouseEvent& event);

	/*
	void setAnchorCoords(int x, int y);
	


	
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
	ddDrawingEditor* getDrawingEditor();
*/
protected:
//	int anchorX, anchorY;
private:
//	ddDrawingEditor *ownerEditor;
	ddIConnectionFigure *toolConnection;
	ddIHandle *handle;

};
#endif
