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

#ifndef DDICONNECTIONFIGURE_H
#define DDICONNECTIONFIGURE_H
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/handles/ddIHandle.h"


class ddIConnector;  //HACK-FIX for circular reference

class ddIConnectionFigure : public ddIFigure
{
public:

	virtual void connectStart(ddIConnector *start)=0;
	virtual void connectEnd(ddIConnector *end)=0;
	virtual void updateConnection()=0;
	virtual void disconnectStart()=0;
	virtual void disconnectEnd()=0;
	virtual bool canConnectStart(ddIFigure *figure)=0;
	virtual bool canConnectEnd(ddIFigure *figure)=0;
	virtual ddPoint connPointAt(int index)=0;
	virtual void splitSegment(int x, int y)=0;

	
	virtual int pointCount()=0;
	virtual ddIConnector* getStartConnector()=0;
	virtual ddIConnector* getEndConnector()=0;
	virtual void setStartConnector(ddIConnector* connector)=0;
	virtual void setEndConnector(ddIConnector* connector)=0;
	virtual ddPoint* getConnStartPoint()=0;
	virtual void setConnStartPoint(ddPoint *point)=0;
	virtual ddPoint* getConnEndPoint()=0;
	virtual void setConnEndPoint(ddPoint *point)=0;
	virtual ddIFigure* getConnStartFigure()=0;
	virtual ddIFigure* getConnEndFigure()=0;
	virtual ddIHandle* getConnStartHandle()=0;
	virtual ddIHandle* getConnEndHandle()=0;

protected:

private:

};
#endif
