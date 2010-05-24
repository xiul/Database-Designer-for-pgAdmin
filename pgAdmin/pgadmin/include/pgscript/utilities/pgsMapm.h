//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsMapm.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#ifndef PGSMAPMLIB_H_
#define PGSMAPMLIB_H_

#include "pgscript/pgScript.h"
#include "mapm-lib/m_apm.h"

WX_DECLARE_OBJARRAY(MAPM, pgsVectorMapm);

class pgsMapm
{

public:

	static wxString pgs_mapm_str(const MAPM & m, const bool & as_int = false);

	static MAPM pgs_mapm_round(const MAPM & m);

	static wxString pgs_mapm_str_fixed(const MAPM & m);

	static wxString pgs_mapm_str_float(const MAPM & m);
	
	static MAPM pgs_str_mapm(const wxString & s);

};

#endif /*PGSMAPMLIB_H_*/
