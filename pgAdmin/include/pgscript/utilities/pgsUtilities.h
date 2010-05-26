//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsUtilities.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSUTILITIES_H_
#define PGSUTILITIES_H_

#include "pgscript/pgScript.h"

class pgsUtilities
{

public:

	static wxString uniform_line_returns(wxString s);
	static wxString escape_quotes(wxString s);
	static wxString unescape_quotes(wxString s);

};

#endif /*PGSUTILITIES_H_*/
