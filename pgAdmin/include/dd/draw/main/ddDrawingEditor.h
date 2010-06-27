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

#ifndef DDDRAWINGEDITOR_H
#define DDDRAWINGEDITOR_H

#include "dd/draw/main/ddDrawingView.h"
#include "dd/draw/tools/ddITool.h"


// Create Array Objects used as base for gqbCollections
class ddDrawingEditor : public ddObject
{
public:
	ddDrawingEditor(wxWindow *owner);
    ~ddDrawingEditor();
	ddDrawingView* view();
	ddDrawing* model();
	ddITool* tool();
	void setTool(ddITool* tool);

protected:

private:
	ddDrawing *_model;
	ddDrawingView *_view;
	ddITool *_tool;



};
#endif
