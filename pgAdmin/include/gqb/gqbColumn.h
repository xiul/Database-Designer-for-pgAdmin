//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbColumn.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbColumn.h - Column Object for GQB
//
//////////////////////////////////////////////////////////////////////////

#ifndef GQBCOLUMN_H
#define GQBCOLUMN_H

// App headers
#include "gqb/gqbObject.h"
#include "gqb/gqbTable.h"

// Create Array Objects used as base for gqbCollections
class gqbColumn : public gqbObject
{
public:
    gqbColumn(gqbObject *parent, wxString name, pgConn *connection);
};
#endif
