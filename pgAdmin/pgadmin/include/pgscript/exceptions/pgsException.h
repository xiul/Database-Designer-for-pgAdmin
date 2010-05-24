//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsException.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSEXCEPTION_H_
#define PGSEXCEPTION_H_

#include "pgscript/pgScript.h"

class pgsException
{
	
protected:
	
	pgsException();
	
public:
	
	virtual ~pgsException();
	
	virtual const wxString message() const = 0;
	
};

#endif /*PGSEXCEPTION_H_*/
