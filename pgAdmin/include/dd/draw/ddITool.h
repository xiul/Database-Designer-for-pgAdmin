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

#ifndef DDITOOL_H
#define DDITOOL_H

#include "dd/draw/ddObject.h"


class ddITool : public ddObject
{
public:
	ddITool();
    ~ddITool();
	virtual void mouseDown(wxMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(wxMouseEvent& event);
	virtual void mouseMove(wxMouseEvent& event);
	virtual void mouseDrag(wxMouseEvent& event);
	virtual void keyDown(wxKeyEvent& event);
	virtual void keyUp(wxKeyEvent& event);
	virtual void activate();
	virtual void deactivate();

	virtual bool activated();
	//DD-TODO: add this virtual IDrawingEditor editor and undoactivity
	virtual bool undoable();

protected:

	bool activatedValue;
	bool undoableValue;
	int anchorX, anchorY;
	void setAnchorCoords(int x, int y);

};
#endif
