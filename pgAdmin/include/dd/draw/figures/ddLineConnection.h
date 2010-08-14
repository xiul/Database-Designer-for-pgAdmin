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

#ifndef DDLINECONNECTION_H
#define DDLINECONNECTION_H
#include "dd/draw/figures/ddPolyLineFigure.h"
//#include "dd/draw/figures/ddIConnectionFigure.h"
#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/handles/ddIHandle.h"

//Multiple Hierarchy used here
class ddLineConnection : public ddPolyLineFigure//, public ddIConnectionFigure
{
public:
	ddLineConnection();
	ddLineConnection(ddIFigure *figure1, ddIFigure *figure2);
	~ddLineConnection();

	virtual void connectStart(ddIConnector *start);
	virtual void connectEnd(ddIConnector *end);
	virtual void disconnectStart();
	virtual void disconnectEnd();
	virtual void updateConnection();
	virtual bool canConnectStart(ddIFigure *figure);
	virtual bool canConnectEnd(ddIFigure *figure);
	//ddPolyLineFigure virtual ddPoint PointAt(int index)=0;
	//virtual void splitSegment(int x, int y)=0;
	virtual bool canConnect();
	virtual void setPointAt (int index, int x, int y);
	virtual ddCollection* handlesEnumerator();
	virtual void basicMoveBy(int x, int y);
	
	virtual void onFigureChanged(ddIFigure *figure);

	//ddPolyLineFigure virtual int pointCount()=0;
	virtual ddIConnector* getStartConnector();
	virtual ddIConnector* getEndConnector();
	virtual void setStartConnector(ddIConnector* connector);
	virtual void setEndConnector(ddIConnector* connector);
	virtual ddIFigure* getStartFigure();
	virtual ddIFigure* getEndFigure();
	virtual ddIHandle* getStartHandle();
	virtual ddIHandle* getEndHandle();
	virtual void addPoint (int x, int y);
	virtual void insertPointAt (int index, int x, int y);

	//using ddPolyLineFigure::pointAt;

/*	//Fix which ambiguos function declared in ddPolyLineFigure and ddIConnectionFigure is going to be used
	using ddPolyLineFigure::getStartPoint;
	using ddPolyLineFigure::getEndPoint;
	using ddPolyLineFigure::setStartPoint;
	using ddPolyLineFigure::setEndPoint;
	using ddPolyLineFigure::splitSegment;
	using ddPolyLineFigure::pointCount;
	//Fix for some reason I need to declare this again to avoid declaration of this class as abstract
	virtual ddPoint* getStartPoint();
	virtual void setStartPoint(ddPoint *point);
	virtual ddPoint* getEndPoint();
	virtual void setEndPoint(ddPoint *point);
	virtual ddPoint* pointAt(int index);
	virtual void splitSegment(int x, int y);
	virtual int pointCount();
	*/

//DD-TODO: HIGH-PRIORITY-FINISH-THIS fix los metodos repetidos para que hagan lo mismo si existen
protected:
	virtual void updateHandlesIndexes();
	virtual void connectFigure (ddIConnector *connector);
	virtual void disconnectFigure (ddIConnector *connector);
private:
	ddIHandle *changeConnStartHandle;
	ddIHandle *changeConnEndHandle; 

	ddIConnector *startConnector;
	ddIConnector *endConnector;
	//ddCollection *connectionHandles;

};
#endif
