//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsModulo.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSMODULO_H_
#define PGSMODULO_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsOperation.h"

class pgsModulo : public pgsOperation
{
	
public:

	pgsModulo(const pgsExpression * left, const pgsExpression * right);

	virtual ~pgsModulo();

	virtual pgsExpression * clone() const;

	pgsModulo(const pgsModulo & that);

	pgsModulo & operator =(const pgsModulo & that);
	
	virtual wxString value() const;
	
	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSMODULO_H_*/
