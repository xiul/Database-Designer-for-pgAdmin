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
#include "dd/draw/figures/ddLineConnection.h"

class ddConnectionCreationTool : public ddAbstractTool
{
public:
	ddConnectionCreationTool(ddDrawingEditor *editor, ddLineConnection *figure);
    ~ddConnectionCreationTool();

	virtual void mouseDrag(ddMouseEvent& event);
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseMove(ddMouseEvent& event);

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
	ddLineConnection *toolConnection;
	ddIHandle *handle;
	int numClicks;
	bool dragged;

};
#endif
