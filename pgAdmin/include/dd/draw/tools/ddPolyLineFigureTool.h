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

#ifndef DDPOLYLINEFIGURETOOL_H
#define DDPOLYLINEFIGURETOOL_H

#include "dd/draw/tools/ddFigureTool.h"


class ddPolyLineFigureTool : public ddFigureTool
{
public:
	ddPolyLineFigureTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddPolyLineFigureTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
protected:
private:
};
#endif
