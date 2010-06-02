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

class ddDrawingView;  //Hack-Fix to avoid circular reference

class ddIHandle : public ddObject
{
public:
	ddIHandle();
    ~ddIHandle();

	virtual bool containsPoint(double x, double y)=0;
	virtual void draw(wxBufferedDC& context);
	virtual wxPoint locate();
	virtual void invokeStart(int x, int y, ddDrawingView *view)=0;
	virtual void invokeStep(int x, int y, ddDrawingView *view)=0;
	virtual void invokeEnd(int x, int y, ddDrawingView *view)=0;
	virtual wxCursor createCursor()=0;
protected:

private:
	ddObject figureOwner; //DD-TODO: change for IFigure but avoid circular reference
	ddRect displayBox;
	double lineWidth;
	//DD-TODO: Add	fillColor and addColor


};
#endif
