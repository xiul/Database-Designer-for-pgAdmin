//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsDifferent.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSDIFFERENT_H_
#define PGSDIFFERENT_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsOperation.h"

class pgsDifferent : public pgsOperation
{

public:

	pgsDifferent(const pgsExpression * left, const pgsExpression * right);

	virtual ~pgsDifferent();

	virtual pgsExpression * clone() const;

	pgsDifferent(const pgsDifferent & that);

	pgsDifferent & operator =(const pgsDifferent & that);

	virtual wxString value() const;
	
	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSDIFFERENT_H_*/
