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

#ifndef DDDATABASEDESIGN_H
#define DDDATABASEDESIGN_H

#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/tools/ddITool.h"

// Create Array Objects used as base for gqbCollections
class ddDatabaseDesign : public wxObject
{
public:
	ddDatabaseDesign(wxWindow *parent);
	~ddDatabaseDesign();
	ddDrawingView* getView();
	ddDrawingEditor* getEditor();
	void addTable(ddIFigure *figure);
	void setTool(ddITool* tool);
protected:

private:
	ddDrawingEditor *draw;
	ddITool *tool;

/*
	
	virtual void add(ddIFigure *figure);
	virtual void remove(ddIFigure *figure);
	virtual bool includes(ddIFigure *figure);
	virtual ddIFigure* findFigure(int x, int y);
	virtual void recalculateDisplayBox();
	virtual void bringToFront(ddIFigure *figure);
	virtual void sendToBack(ddIFigure *figure);
	virtual ddRect& DisplayBox();
	virtual ddIteratorBase* figuresEnumerator();
	virtual ddIteratorBase* figuresInverseEnumerator();
	virtual void deleteFigures();

/* DD-TODO: agregar estos manejadores de eventos
		event EventHandler <DrawingEventArgs> DrawingInvalidated;
		event EventHandler <DrawingEventArgs> SizeAllocated;
	ddCollection *figures;
	ddCollection *handles;
	ddRect displayBox;
	//DD-TODO: inicializasr listas

*/

};
#endif
