//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsStmt.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"
#include "pgscript/statements/pgsStmt.h"

pgsStmt::pgsStmt(pgsThread * app) :
	m_line(0), m_app(app)
{

}

pgsStmt::~pgsStmt()
{

}

void pgsStmt::set_position(int line)
{
	m_line = line;
}

int pgsStmt::line() const
{
	return m_line;
}
