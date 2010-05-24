//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbDatabase.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbDatabase.h - Database object for GQB.
//
//////////////////////////////////////////////////////////////////////////

#ifndef GQBDATABASE_H
#define GQBDATABASE_H

// App headers
#include "gqb/gqbObject.h"
#include "gqb/gqbSchema.h"
#include "gqb/gqbBrowser.h"

class gqbDatabase : public gqbObject
{
public:
    gqbDatabase(wxString name, pgConn *connection);
    void createObjects(gqbBrowser *_tablesBrowser);

private:
    enum typeSchema
    {
        GQB_CATALOG,
        GQB_OTHER
    };
    void createSchemas(gqbBrowser *tablesBrowser, wxTreeItemId parentNode,typeSchema MetaType, int indexImage);
};
#endif
