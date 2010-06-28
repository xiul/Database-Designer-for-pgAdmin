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

#include "dd/draw/main/ddObject.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/utilities/ddPoint.h"

class ddDrawingView;  //Hack-Fix to avoid circular reference
class ddIFigure;

class ddIHandle : public ddObject
{
public:
	ddIHandle(ddIFigure *owner);
    ~ddIHandle();
	
	static const int size = 4;

	virtual bool containsPoint(int x, int y);
	virtual void draw(wxBufferedDC& context, ddDrawingView *view)=0;
	virtual ddPoint* locate()=0;
	virtual void invokeStart(int x, int y, ddDrawingView *view)=0;
	virtual void invokeStep(int x, int y, ddDrawingView *view)=0;
	virtual void invokeEnd(int x, int y, ddDrawingView *view)=0;
	virtual wxCursor& createCursor()=0;
	virtual ddRect& getDisplayBox();
protected:
	virtual ddIFigure* getOwner();
private:
	ddIFigure *figureOwner;
	ddRect displayBox;
	double lineWidth;
	//DD-TODO: Add	fillColor and addColor


};
#endif
