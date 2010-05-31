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

#ifndef DDIHANDLE_H
#define DDIHANDLE_H

#include "dd/draw/ddObject.h"
#include "dd/draw/ddRect.h"



// Create Array Objects used as base for gqbCollections
class ddIHandle : public ddObject
{
public:
	ddIHandle();
    ~ddIHandle();

	virtual bool containsPoint(double x, double y)=0;
	virtual void draw(wxBufferedDC& context);
	virtual wxPoint locate();


	/* DD-TODO: add this methods
		void InvokeStart (double x, double y, IDrawingView view);
		void InvokeStep (double x, double y, IDrawingView view);
		void InvokeEnd (double x, double y, IDrawingView view);
		Gdk.Cursor CreateCursor ();
		*/
	virtual int getIndex() { return index; };
	virtual void setIndex(int indx) { index=indx; };
protected:

private:
	ddObject figureOwner; //DD-TODO: change for IFigure but avoid circular reference
	ddRect displayBox;
	double lineWidth;
	int index;
	//DD-TODO: Add	fillColor and addColor


};
#endif
