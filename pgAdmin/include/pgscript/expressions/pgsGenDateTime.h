//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsGenDateTime.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSGENDATETIME_H_
#define PGSGENDATETIME_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsExpression.h"

class pgsGenDateTime : public pgsExpression
{

private:

	const pgsExpression * m_min;
	const pgsExpression * m_max;
	const pgsExpression * m_sequence;
	const pgsExpression * m_seed;

public:

	pgsGenDateTime(const pgsExpression * min, const pgsExpression * max,
			const pgsExpression * sequence, const pgsExpression * seed);

	virtual ~pgsGenDateTime();

	virtual pgsExpression * clone() const;

	pgsGenDateTime(const pgsGenDateTime & that);

	pgsGenDateTime & operator =(const pgsGenDateTime & that);

public:

	virtual wxString value() const;

	virtual pgsOperand eval(pgsVarMap & vars) const;

};

#endif /*PGSGENDATETIME_H_*/
