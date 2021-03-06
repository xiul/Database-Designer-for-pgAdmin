//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsIdent.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSIDENT_H_
#define PGSIDENT_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsExpression.h"

class pgsIdent : public pgsExpression
{

protected:

	wxString m_name;

public:

	pgsIdent(const wxString & name);

	virtual ~pgsIdent();

	/* pgsIdent(const pgsIdent & that); */

	/* pgsIdent & operator=(const pgsIdent & that); */

	virtual pgsExpression * clone() const;
	
	virtual wxString value() const;

	virtual pgsOperand eval(pgsVarMap & vars) const;
	
public:
	
	static const wxString m_now;

};

#endif /*PGSIDENT_H_*/
