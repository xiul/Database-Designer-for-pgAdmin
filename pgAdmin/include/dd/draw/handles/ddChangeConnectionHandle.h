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

#ifndef DDCHANGECONNECTIONHANDLE_H
#define DDCHANGECONNECTIONHANDLE_H

#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/main/ddDrawing.h"

/*class ddDrawingView;  //Hack-Fix to avoid circular reference
class ddIFigure;
*/
class ddChangeConnectionHandle : public ddIHandle
{
public:
	ddChangeConnectionHandle(ddLineConnection *owner);
    ~ddChangeConnectionHandle();
	
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual wxCursor createCursor();
	virtual void invokeStart(ddMouseEvent& event, ddDrawingView *view);
	virtual void invokeStep(ddMouseEvent& event, ddDrawingView *view);
	virtual void invokeEnd(ddMouseEvent& event, ddDrawingView *view);
	virtual ddIConnector* target()=0;
	virtual void disconnect()=0;
	virtual void connect(ddIConnector *connector)=0;
	virtual void setPoint(ddPoint p)=0;
	virtual bool isConnectionPossible(ddIFigure *figure)=0;
	ddIFigure* findConnectableFigure(int x, int y, ddDrawing *drawing);
	ddIConnector* findConnectionTarget(int x, int y, ddDrawing *drawing);
protected:
	ddLineConnection *connection;
	ddIFigure *targetFigure;
private:
	ddIConnector *originalTarget;
};
#endif
