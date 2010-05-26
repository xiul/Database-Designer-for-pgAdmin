//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsTrim.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSTRIM_H_
#define PGSTRIM_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsExpression.h"

class pgsTrim : public pgsExpression
{
	
private:
	
	const pgsExpression * m_exp;
	
public:

	pgsTrim(const pgsExpression * exp);

	virtual ~pgsTrim();

	pgsTrim(const pgsTrim & that);

	pgsTrim & operator=(const pgsTrim & that);

	virtual pgsExpression * clone() const;
	
	virtual wxString value() const;

	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSTRIM_H_*/
