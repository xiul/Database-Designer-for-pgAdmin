//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsBreakStmt.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"
#include "pgscript/statements/pgsBreakStmt.h"

#include "pgscript/exceptions/pgsBreakException.h"

pgsBreakStmt::pgsBreakStmt(pgsThread * app) :
	pgsStmt(app)
{

}

pgsBreakStmt::~pgsBreakStmt()
{

}

void pgsBreakStmt::eval(pgsVarMap & vars) const
{
	throw pgsBreakException();
}
