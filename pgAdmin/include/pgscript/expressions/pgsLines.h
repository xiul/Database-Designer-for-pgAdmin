//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsLines.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSLINES_H_
#define PGSLINES_H_

#include "pgscript/pgScript.h"
#include "pgscript/expressions/pgsExpression.h"

class pgsLines : public pgsExpression
{
	
private:
	
	wxString m_name;
	
public:

	pgsLines(const wxString & name);

	virtual ~pgsLines();

	/* pgsLines(const pgsLines & that); */

	/* pgsLines & operator=(const pgsLines & that); */

	virtual pgsExpression * clone() const;
	
	virtual wxString value() const;

	virtual pgsOperand eval(pgsVarMap & vars) const;
	
};

#endif /*PGSLINES_H_*/
