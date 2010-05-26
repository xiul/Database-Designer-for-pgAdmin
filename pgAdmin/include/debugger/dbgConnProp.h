//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dbgConnProp.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dbgConnProp.h - debugger 
//
//////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// class dbgConnProp
//
//  dbgConnProp object is used to hold a set of connection properties, that is.
//  it's a collection of all of the information that we need in order to connect
//  to a server.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef DBGCONNPROP_H
#define DBGCONNPROP_H

class dbgConnProp
{

public:
	wxString	m_host;			// Host name (or IP-address)
	wxString	m_database;		// Database name
	wxString	m_userName;		// User name	
	wxString	m_password;		// Password
	wxString	m_port;			// Port number
	wxString	m_debugPort;	// Port number for debugger connection
	int		    m_sslMode;		// SSL Mode
	wxString	m_applicationName;	// Application name, only on 8.5
};

#endif
