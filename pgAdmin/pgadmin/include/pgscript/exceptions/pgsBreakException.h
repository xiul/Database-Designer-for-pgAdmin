//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsBreakException.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSBREAKEXCEPTION_H_
#define PGSBREAKEXCEPTION_H_

#include "pgscript/pgScript.h"
#include "pgscript/exceptions/pgsException.h"

class pgsBreakException : public pgsException
{
	
public:
	
	pgsBreakException();
	
	virtual ~pgsBreakException();
	
	virtual const wxString message() const;
	
};

#endif /*PGSBREAKEXCEPTION_H_*/
