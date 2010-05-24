//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgSchema.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgSchema.h - Schemaproperty 
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_SCHEMAPROP
#define __DLG_SCHEMAPROP

#include "dlg/dlgProperty.h"

class pgSchema;

class dlgSchema : public dlgSecurityProperty
{
public:
    dlgSchema(pgaFactory *factory, frmMain *frame, pgSchema *db);
    int Go(bool modal);

    void CheckChange();
    wxString GetSql();
    pgObject *CreateObject(pgCollection *collection);
    pgObject *GetObject();

private:
    pgSchema *schema;

#ifdef __WXMAC__
    void OnChangeSize(wxSizeEvent &ev);
#endif

    DECLARE_EVENT_TABLE()
};


#endif
