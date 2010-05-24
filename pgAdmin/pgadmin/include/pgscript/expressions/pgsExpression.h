//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsExpression.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSEXPRESSION_H_
#define PGSEXPRESSION_H_

#include "pgscript/pgScript.h"
#include "pgscript/utilities/pgsCopiedPtr.h"

class pgsProgram;
class pgsVariable;

WX_DECLARE_STRING_HASH_MAP(pgsCopiedPtr<pgsVariable>, pgsVarMap);
typedef pgsCopiedPtr<pgsVariable> pgsOperand;

class pgsExpression
{

protected:

	pgsExpression();

public:

	virtual ~pgsExpression();

	virtual pgsExpression * clone() const = 0;

	/* pgsExpression(const pgsExpression & that); */

	/* pgsExpression & operator =(const pgsExpression & that); */

public:

	virtual wxString value() const = 0;

	virtual pgsOperand eval(pgsVarMap & vars) const = 0;
	
};

#endif /*PGSEXPRESSION_H_*/
