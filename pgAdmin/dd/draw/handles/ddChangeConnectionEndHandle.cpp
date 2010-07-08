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
#include "dd/draw/handles/ddChangeConnectionEndHandle.h"
#include "dd/draw/utilities/ddPoint.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddChangeConnectionEndHandle::ddChangeConnectionEndHandle(ddLineConnection *owner):
ddChangeConnectionHandle(owner)
{
}

ddChangeConnectionEndHandle::~ddChangeConnectionEndHandle()
{
}

ddPoint& ddChangeConnectionEndHandle::locate()
{
	return connection->getEndPoint();
}

ddIConnector* ddChangeConnectionEndHandle::target()
{
	return connection->getEndConnector();
}

void ddChangeConnectionEndHandle::connect(ddIConnector *connector)
{
	connection->connectEnd(connector);
}

void ddChangeConnectionEndHandle::disconnect()
{
	connection->disconnectEnd();
}

bool ddChangeConnectionEndHandle::isConnectionPossible(ddIFigure *figure)
{
	if(!figure->includes(connection) && figure->canConnect() && connection->canConnectEnd(figure))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ddChangeConnectionEndHandle::setPoint(ddPoint p)
{
	connection->setEndPoint(p);
	//DD-TODO: avoid this memory leak when a point have been overwritten
}