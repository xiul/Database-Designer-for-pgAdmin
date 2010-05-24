//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsAssertException.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSASSERTEXCEPTION_H_
#define PGSASSERTEXCEPTION_H_

#include "pgscript/pgScript.h"
#include "pgscript/exceptions/pgsException.h"

class pgsAssertException : public pgsException
{
	
protected:
		
	const wxString m_message;
	
public:
	
	pgsAssertException(const wxString & message);
	
	virtual ~pgsAssertException();
	
	virtual const wxString message() const;
	
};

#endif /*PGSASSERTEXCEPTION_H_*/
