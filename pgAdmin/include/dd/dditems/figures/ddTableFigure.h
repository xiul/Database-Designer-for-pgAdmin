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

#ifndef DDTABLEFIGURE_H
#define DDTABLEFIGURE_H
#include "dd/draw/figures/ddCompositeFigure.h"
#include "dd/draw/figures/ddRectangleFigure.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/dditems/figures/ddTextColumnFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"


// Create Array Objects used as base for gqbCollections
class ddTableFigure : public ddCompositeFigure
{
public:
	ddTableFigure(int x, int y);
    ~ddTableFigure();
	void addColumn(ddColumnFigure *column);
	void removeColumn(ddColumnFigure *column);
	void updateTableSize();
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual void drawSelected(wxBufferedDC& context, ddDrawingView *view);
	void resetColPosition(ddColumnFigure *column);
	bool deleteColumnActivated();
	void toggleColumnDeleteMode(bool disable=false);
	void calculateBars(ddDrawingView *view);
protected:

private:
	ddRectangleFigure *rectangleFigure;
	ddTextColumnFigure *tableTitle;
	bool fromSelToNOSel;
	bool deleteColumnMode;
	int internalPadding, externalPadding;
	int minWidth, minHeight;
	ddPoint colsTopLeft, colsTopRight, colsBottomLeft, colsBottomRight;
	ddPoint idxsTopLeft, idxsTopRight, idxsBottomLeft, idxsBottomRight;
};
#endif
