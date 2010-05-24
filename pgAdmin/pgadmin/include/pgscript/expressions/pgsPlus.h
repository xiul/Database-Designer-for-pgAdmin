//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsPlus.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSPLUS_H_
#define PGSPLUS_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsOperation.h"

class pgsPlus : public pgsOperation
{
	
public:

	pgsPlus(const pgsExpression * left, const pgsExpression * right);

	virtual ~pgsPlus();

	virtual pgsExpression * clone() const;
	
	pgsPlus(const pgsPlus & that);

	pgsPlus & operator =(const pgsPlus & that);
	
	virtual wxString value() const;
	
	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSPLUS_H_*/
