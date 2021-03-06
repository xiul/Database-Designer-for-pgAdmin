//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsObjectGen.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSOBJECTGEN_H_
#define PGSOBJECTGEN_H_

#include "pgscript/pgScript.h"
#include <wx/datetime.h>

class pgsObjectGen
{

protected:

	long m_seed;

	pgsObjectGen(const long & seed = wxDateTime::GetTimeNow());

	/* pgsObjectGen & operator =(const pgsObjectGen & that); */

	/* pgsObjectGen(const pgsObjectGen & that); */

public:

	virtual ~pgsObjectGen();

	virtual wxString random() = 0;
	
	virtual pgsObjectGen * clone() = 0;

};

#endif /*PGSOBJECTGEN_H_*/
