//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsLowerEqual.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSLOWEREQUAL_H_
#define PGSLOWEREQUAL_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsOperation.h"

class pgsLowerEqual : public pgsOperation
{
	
public:

	pgsLowerEqual(const pgsExpression * left, const pgsExpression * right);

	virtual ~pgsLowerEqual();

	virtual pgsExpression * clone() const;

	pgsLowerEqual(const pgsLowerEqual & that);

	pgsLowerEqual & operator =(const pgsLowerEqual & that);

	virtual wxString value() const;
	
	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSLOWEREQUAL_H_*/
