//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsArithmeticException.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"
#include "pgscript/exceptions/pgsArithmeticException.h"

pgsArithmeticException::pgsArithmeticException(const wxString & left, const wxString & right) :
	pgsException(), m_left(left), m_right(right)
{
	
}

pgsArithmeticException::~pgsArithmeticException()
{
	
}

const wxString pgsArithmeticException::message() const
{
	return wxString() << PGSOUTEXCEPTION <<
		wxString::Format(_("Arithmetic Exception - Operation impossible between '%s' and '%s'"),
			m_left.c_str(), m_right.c_str());
}
