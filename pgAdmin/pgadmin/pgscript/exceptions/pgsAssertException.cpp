//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsAssertException.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"
#include "pgscript/exceptions/pgsAssertException.h"

pgsAssertException::pgsAssertException(const wxString & message) :
	m_message(message)
{
	
}

pgsAssertException::~pgsAssertException()
{

}

const wxString pgsAssertException::message() const
{
	return wxString() << PGSOUTEXCEPTION << _("Assert Exception - ") << m_message;
}
