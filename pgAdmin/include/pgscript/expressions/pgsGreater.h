//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsGreater.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSGREATER_H_
#define PGSGREATER_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsOperation.h"

class pgsGreater : public pgsOperation
{
	
public:

	pgsGreater(const pgsExpression * left, const pgsExpression * right);

	virtual ~pgsGreater();

	virtual pgsExpression * clone() const;

	pgsGreater(const pgsGreater & that);

	pgsGreater & operator =(const pgsGreater & that);

	virtual wxString value() const;
	
	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSGREATER_H_*/
