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

#ifndef DDDRAGTRACKERTOOL_H
#define DDDRAGTRACKERTOOL_H

#include "dd/draw/ddObject.h"
#include "dd/draw/ddITool.h"
#include "dd/draw/ddIFigure.h"
#include "dd/draw/ddDrawingEditor.h"
#include "dd/draw/ddAbstractTool.h"


class ddDragTrackerTool : public ddAbstractTool
{
public:
	ddDragTrackerTool(ddDrawingEditor *editor, ddIFigure *anchor);
    ~ddDragTrackerTool();

	void setLastCoords(int x, int y);
	bool hasMoved();
	virtual void mouseDown(wxMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(wxMouseEvent& event);
	virtual void mouseDrag(wxMouseEvent& event);

protected:
	ddIFigure *anchorFigure;
	int lastX, lastY;
	bool hasMovedValue;

private:

	ddDrawingView *view;


	


};
#endif
