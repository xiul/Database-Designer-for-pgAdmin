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

#ifndef DDCHANGECONNECTIONENDHANDLE_H
#define DDCHANGECONNECTIONENDHANDLE_H

#include "dd/draw/handles/ddChangeConnectionHandle.h"
#include "dd/draw/figures/ddLineConnection.h"

class ddChangeConnectionEndHandle : public ddChangeConnectionHandle
{
public:
	ddChangeConnectionEndHandle(ddLineConnection *owner);
    ~ddChangeConnectionEndHandle();
	virtual ddPoint& locate();
	virtual ddIConnector* target();
	virtual void disconnect();
	virtual void connect(ddIConnector *connector);
	virtual bool isConnectionPossible(ddIFigure *figure);
	virtual void setPoint(ddPoint p);
};
#endif
