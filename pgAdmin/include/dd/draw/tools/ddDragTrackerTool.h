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

#include "dd/draw/main/ddObject.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/tools/ddAbstractTool.h"


class ddDragTrackerTool : public ddAbstractTool
{
public:
	ddDragTrackerTool(ddDrawingEditor *editor, ddIFigure *anchor);
    ~ddDragTrackerTool();

	void setLastCoords(int x, int y);
	bool hasMoved();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(ddMouseEvent& event);
	virtual void mouseDrag(ddMouseEvent& event);

protected:
	ddIFigure *anchorFigure;
	bool hasMovedValue;

private:
	int lastX, lastY;
	ddDrawingView *view;


	


};
#endif
