//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsParenthesis.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSPARENTHESIS_H_
#define PGSPARENTHESIS_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsOperation.h"

class pgsParenthesis : public pgsOperation
{
	
public:

	pgsParenthesis(const pgsExpression * left);

	virtual ~pgsParenthesis();

	virtual pgsExpression * clone() const;

	pgsParenthesis(const pgsParenthesis & that);

	pgsParenthesis & operator =(const pgsParenthesis & that);

	virtual wxString value() const;
	
	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSPARENTHESIS_H_*/
