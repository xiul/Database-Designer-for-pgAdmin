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

	virtual bool containsPoint(int x, int y);
	virtual void draw(wxBufferedDC& context)=0;
	virtual ddPoint* locate()=0;
	virtual void invokeStart(int x, int y, ddDrawingView *view)=0;
	virtual void invokeStep(int x, int y, ddDrawingView *view)=0;
	virtual void invokeEnd(int x, int y, ddDrawingView *view)=0;
	virtual wxCursor& createCursor()=0;
protected:
	virtual ddIFigure* getOwner();
	virtual ddRect& getDisplayBox();
private:
	ddIFigure *figureOwner; //DD-TODO: change for IFigure but avoid circular reference
	ddRect displayBox;
	double lineWidth;
	//DD-TODO: Add	fillColor and addColor


};
#endif
