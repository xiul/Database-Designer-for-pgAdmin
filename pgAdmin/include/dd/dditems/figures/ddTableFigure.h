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
public:  //DD-TODO: put private unneeded public methods
	ddTableFigure(int x, int y);
    ~ddTableFigure();
	void addColumn(ddColumnFigure *column);
	void removeColumn(ddColumnFigure *column);
	void updateTableSize();
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual void drawSelected(wxBufferedDC& context, ddDrawingView *view);
	void recalculateColsPos();
	bool deleteColumnActivated();
	void toggleColumnDeleteMode(bool disable=false);
	void setColsRowsWindow(int num);
	ddRect& getColsSpace();
protected:

private:
	//Main Rectangle Sizes
	ddRect fullSizeRect, titleRect, titleColsRect, colsRect, titleIndxsRect, indxsRect;
	ddRect unScrolledColsRect;
//	ddRect scrolledFullSizeRect, scrolledTitleRect, scrolledTitleColsRect, scrolledColsRect, scrolledTitleIndxsRect, scrolledIndxsRect;
	//Rectangle item counters
	int colsRowsSize, colsWindow, idxsRowsSize, idxsWindow;
	//vector indexes
	int maxColIndex,minIdxIndex,maxIdxIndex;
	//position
	int beginDrawCols, beginDrawIdxs;
	
	//Default Figures
	ddRectangleFigure *rectangleFigure;
	ddTextColumnFigure *tableTitle;

	//helper variables
	bool fromSelToNOSel;
	bool deleteColumnMode;
	int internalPadding, externalPadding;
	bool calcScrolled;

	//methods
	int getHeightFontMetric(wxString text, wxFont font);
	int getColDefaultHeight(wxFont font);
	int getFiguresMaxWidth();
	void calcRectsAreas();
};
#endif
