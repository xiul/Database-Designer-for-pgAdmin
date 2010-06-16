//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawing.cpp - Container for figures that send changed events to Listeners whenever 
//	a part of its area was invalidated. Using the design pattern observer to decouple the
//	Drawing from its views and to enable multiple views .
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/handles/ddChangeConnectionStartHandle.h"
#include "dd/draw/utilities/ddPoint.h"

ddChangeConnectionStartHandle::ddChangeConnectionStartHandle(ddIConnectionFigure *owner):
ddChangeConnectionHandle(owner)
{
}

ddChangeConnectionStartHandle::~ddChangeConnectionStartHandle()
{
}

ddPoint* ddChangeConnectionStartHandle::locate()
{
	return connection->getConnStartPoint();
}

ddIConnector* ddChangeConnectionStartHandle::target()
{
	return connection->getStartConnector();
}

void ddChangeConnectionStartHandle::connect(ddIConnector *connector)
{
	connection->connectStart(connector);
}

void ddChangeConnectionStartHandle::disconnect()
{
	connection->disconnectStart();
}

bool ddChangeConnectionStartHandle::isConnectionPossible(ddIFigure *figure)
{
	if(!figure->includes(connection) && figure->canConnect() && connection->canConnectStart(figure))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ddChangeConnectionStartHandle::setPoint(ddPoint* p)
{
	connection->setConnStartPoint(p);
	//DD-TODO: avoid this memory leak when a point have been overwritten
}