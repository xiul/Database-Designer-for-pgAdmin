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

#ifndef ddDrawing_H
#define ddDrawing_H

#include "dd/draw/ddIFigure.h"

// Create Array Objects used as base for gqbCollections
class ddDrawing : public wxObject
{
public:
	ddDrawing();
	virtual ~ddDrawing();
	virtual void add(ddIFigure *figure);
	virtual void remove(ddIFigure *figure);
/*	virtual void draw(wxBufferedDC& context, ddCollection figures)=0;
	virtual void draw(wxBufferedDC& context)=0;
	*/
	virtual bool includes(ddIFigure *figure);
	virtual ddIFigure* findFigure(int x, int y);
	virtual void recalculateDisplayBox();
	virtual void bringToFront(ddIFigure figure);
	virtual void sendToBack(ddIFigure figure);
	virtual ddRect& DisplayBox();
	virtual ddIteratorBase* figuresEnumerator();
	virtual ddIteratorBase* ddDrawing::figuresInverseEnumerator();
	virtual void deleteFigures();

/* DD-TODO: agregar estos manejadores de eventos
		event EventHandler <DrawingEventArgs> DrawingInvalidated;
		event EventHandler <DrawingEventArgs> SizeAllocated;
*/

protected:

private:
	ddCollection *figures;
	ddCollection *handles;
	ddRect displayBox;
	//DD-TODO: inicializasr listas

};
#endif
