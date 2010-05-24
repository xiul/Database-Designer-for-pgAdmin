//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsAnd.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSAND_H_
#define PGSAND_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsOperation.h"

class pgsAnd : public pgsOperation
{
	
public:

	pgsAnd(const pgsExpression * left, const pgsExpression * right);

	virtual ~pgsAnd();

	virtual pgsExpression * clone() const;

	pgsAnd(const pgsAnd & that);

	pgsAnd & operator =(const pgsAnd & that);

	virtual wxString value() const;
	
	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSAND_H_*/
