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
#include "dd/draw/figures/ddIConnectionFigure.h"
#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/handles/ddIHandle.h"

//Multiple Hierarchy used here
class ddLineConnection : public ddPolyLineFigure, public ddIConnectionFigure
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
	virtual ddPoint connPointAt(int index)=0;
	virtual void splitSegment(int x, int y)=0;
	virtual bool canConnect();
	virtual void setPointAt (int index, int x, int y);
	virtual ddCollection* handlesEnumerator();
	virtual void basicMoveBy(int x, int y);
	
	virtual int pointCount()=0;
	virtual ddIConnector* getStartConnector();
	virtual ddIConnector* getEndConnector();
	virtual void setStartConnector(ddIConnector* connector);
	virtual void setEndConnector(ddIConnector* connector);
	virtual ddPoint* getConnStartPoint()=0;
	virtual void setConnStartPoint(ddPoint *point)=0;
	virtual ddPoint* getConnEndPoint()=0;
	virtual void setConnEndPoint(ddPoint *point)=0;
	virtual ddIFigure* getConnStartFigure();
	virtual ddIFigure* getConnEndFigure();
	virtual ddIHandle* getConnStartHandle();
	virtual ddIHandle* getConnEndHandle();
//DD-TODO: HIGH-PRIORITY-FINISH-THIS fix los metodos repetidos para que hagan lo mismo
protected:

private:
	void connectFigure (ddIConnector *connector);
	void disconnectFigure (ddIConnector *connector);

	ddIConnector *startConnector;
	ddIConnector *endConnector;
	ddCollection *connectionHandles;

};
#endif
