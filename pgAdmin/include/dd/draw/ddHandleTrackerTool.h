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

#ifndef DDHANDLETRACKERTOOL_H
#define DDHANDLETRACKERTOOL_H

#include "dd/draw/ddObject.h"
#include "dd/draw/ddITool.h"
#include "dd/draw/ddIHandle.h"
#include "dd/draw/ddDrawingEditor.h"
#include "dd/draw/ddAbstractTool.h"


class ddHandleTrackerTool : public ddAbstractTool
{
public:
	ddHandleTrackerTool(ddDrawingEditor *editor, ddIHandle *anchor);
    ~ddHandleTrackerTool();

	virtual void mouseDown(wxMouseEvent& event);  //Mouse Right Click
	virtual void mouseUp(wxMouseEvent& event);
	virtual void mouseDrag(wxMouseEvent& event);

protected:
	ddIHandle *anchorHandle;

private:

	ddDrawingView *view;


	


};
#endif
