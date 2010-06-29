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

#ifndef DDABSTRACTTOOL_H
#define DDABSTRACTTOOL_H

#include "dd/draw/main/ddObject.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/main/ddDrawingEditor.h"


class ddAbstractTool : public ddITool
{
public:
	ddAbstractTool(ddDrawingEditor *editor);
    ~ddAbstractTool();

	void setAnchorCoords(int x, int y);
	
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseMove(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
	ddDrawingEditor* getDrawingEditor();

protected:
	int anchorX, anchorY;
private:
	ddDrawingEditor *ownerEditor;

};
#endif
