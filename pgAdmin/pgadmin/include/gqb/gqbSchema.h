//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbSchema.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbSchema.h - Schema object for GQB
//
//////////////////////////////////////////////////////////////////////////

#ifndef GQBSCHEMA_H
#define GQBSCHEMA_H

// App headers
#include "gqb/gqbObject.h"
#include "gqb/gqbTable.h"

class gqbSchema : public gqbObject
{
public:
    gqbSchema(gqbObject *parent, wxString name, pgConn *connection, OID oid);
    void createObjects(gqbBrowser *tablesBrowser, OID oidVal, wxTreeItemId parentNode, int tableImage, int viewImage, int xTableImage);

private:
    void createTables(gqbBrowser *tablesBrowser, wxTreeItemId parentNode, OID oidVal, int tableImage, int viewImage, int xTableImage);
};
#endif
