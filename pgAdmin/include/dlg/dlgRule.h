//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgRule.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgRule.h - Rule property 
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_RULEPROP
#define __DLG_RULEPROP

#include "dlg/dlgProperty.h"

class pgTable;
class pgRule;
class ctlSQLBox;

class dlgRule : public dlgProperty
{
public:
    dlgRule(pgaFactory *factory, frmMain *frame, pgRule *r, pgTable *tab);
    int Go(bool modal);

    void CheckChange();
    wxString GetSql();
    pgObject *CreateObject(pgCollection *collection);
    pgObject *GetObject();

private:
    pgTable *table;
    pgRule *rule;
    wxString oldDefinition;

    bool didChange();

    DECLARE_EVENT_TABLE()
};


#endif
