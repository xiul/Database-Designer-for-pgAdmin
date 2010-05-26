//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsParameterException.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSPARAMETEREXCEPTION_H_
#define PGSPARAMETEREXCEPTION_H_

#include "pgscript/pgScript.h"
#include "pgscript/exceptions/pgsException.h"

class pgsParameterException : public pgsException
{
	
protected:
	
	const wxString m_message;
	
public:
	
	pgsParameterException(const wxString & message = wxT("unknown"));
	
	virtual ~pgsParameterException();
	
	virtual const wxString message() const;
	
};

#endif /*PGSPARAMETEREXCEPTION_H_*/
