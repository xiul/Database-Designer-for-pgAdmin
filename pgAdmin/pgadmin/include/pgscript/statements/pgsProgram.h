//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsProgram.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSPROGRAM_H_
#define PGSPROGRAM_H_

#include "pgscript/pgScript.h"
#include "pgscript/objects/pgsVariable.h"

#include <wx/thread.h>

class pgsStmtList;

class pgsProgram
{

private:

	pgsVarMap & m_vars;

public:

	pgsProgram(pgsVarMap & vars);

	~pgsProgram();

	void dump();

	static void dump(const pgsVarMap & vars);
	
	void eval(pgsStmtList * stmt_list);

private:

	pgsProgram(const pgsProgram & that);

	pgsProgram & operator=(const pgsProgram & that);

};

#endif /*PGSPROGRAM_H_*/
