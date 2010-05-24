//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsAssertStmt.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"
#include "pgscript/statements/pgsAssertStmt.h"

#include "pgscript/exceptions/pgsAssertException.h"

pgsAssertStmt::pgsAssertStmt(const pgsExpression * cond, pgsThread * app) :
	pgsStmt(app), m_cond(cond)
{

}

pgsAssertStmt::~pgsAssertStmt()
{
	pdelete(m_cond);
}

void pgsAssertStmt::eval(pgsVarMap & vars) const
{
	pgsOperand result = m_cond->eval(vars);
	if (!result->pgs_is_true())
	{
		throw pgsAssertException(m_cond->value());
	}
}
