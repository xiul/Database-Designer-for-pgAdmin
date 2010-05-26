//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsInterruptException.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSINTERRUPTEXCEPTION_H_
#define PGSINTERRUPTEXCEPTION_H_

#include "pgscript/pgScript.h"
#include "pgscript/exceptions/pgsException.h"

class pgsInterruptException : public pgsException
{
	
public:
	
	pgsInterruptException();
	
	virtual ~pgsInterruptException();
	
	virtual const wxString message() const;
	
};

#endif /*PGSINTERRUPTEXCEPTION_H_*/
