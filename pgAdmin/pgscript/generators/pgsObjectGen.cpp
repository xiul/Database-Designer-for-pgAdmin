//////////////////////////////////////////////////////////////////////////
//
// pgScript - PostgreSQL Tools
// RCS-ID:      $Id: pgsObjectGen.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
//////////////////////////////////////////////////////////////////////////


#include "pgAdmin3.h"
#include "pgscript/generators/pgsObjectGen.h"

pgsObjectGen::pgsObjectGen(const long & seed) :
	m_seed(seed == 0 ? 1 : seed)
{

}

pgsObjectGen::~pgsObjectGen()
{

}
