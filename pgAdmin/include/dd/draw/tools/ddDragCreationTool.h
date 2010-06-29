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

#ifndef DDDRAGCREATIONTOOL_H
#define DDDRAGCREATIONTOOL_H

#include "dd/draw/tools/ddCreationTool.h"
#include "dd/draw/main/ddDrawingEditor.h"


class ddDragCreationTool : public ddCreationTool
{
public:
	ddDragCreationTool(ddDrawingEditor *editor, ddIFigure *prototype);
    ~ddDragCreationTool();
	virtual void mouseDrag(ddMouseEvent& event);
};
#endif
