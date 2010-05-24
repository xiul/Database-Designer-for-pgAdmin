//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsExpressionStmt.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"
#include "pgscript/statements/pgsExpressionStmt.h"

pgsExpressionStmt::pgsExpressionStmt(const pgsExpression * var, pgsThread * app) :
	pgsStmt(app), m_var(var)
{

}

pgsExpressionStmt::~pgsExpressionStmt()
{
	pdelete(m_var)
}

void pgsExpressionStmt::eval(pgsVarMap & vars) const
{
	m_var->eval(vars);
}
