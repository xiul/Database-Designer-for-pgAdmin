//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsOr.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSOR_H_
#define PGSOR_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsOperation.h"

class pgsOr : public pgsOperation
{
	
public:

	pgsOr(const pgsExpression * left, const pgsExpression * right);

	virtual ~pgsOr();

	virtual pgsExpression * clone() const;

	pgsOr(const pgsOr & that);

	pgsOr & operator =(const pgsOr & that);

	virtual wxString value() const;
	
	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSOR_H_*/
