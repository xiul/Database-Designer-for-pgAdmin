//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsOver.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSOVER_H_
#define PGSOVER_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsOperation.h"

class pgsOver : public pgsOperation
{
	
public:

	pgsOver(const pgsExpression * left, const pgsExpression * right);

	virtual ~pgsOver();

	virtual pgsExpression * clone() const;
	
	pgsOver(const pgsOver & that);

	pgsOver & operator =(const pgsOver & that);
	
	virtual wxString value() const;
	
	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSOVER_H_*/
