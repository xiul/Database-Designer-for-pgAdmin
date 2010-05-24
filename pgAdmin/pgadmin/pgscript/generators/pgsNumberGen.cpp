//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsNumberGen.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"
#include "pgscript/generators/pgsNumberGen.h"

pgsNumberGen::pgsNumberGen(const MAPM & range) :
	m_range(range)
{

}

pgsNumberGen::~pgsNumberGen()
{

}
