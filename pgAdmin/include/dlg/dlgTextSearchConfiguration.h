//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgTextSearchConfiguration.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgTextSearchConfiguration.h - Text Search Configuration property 
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_TSCONFIGURATIONPROP
#define __DLG_TSCONFIGURATIONPROP

#include "dlg/dlgProperty.h"

class pgSchema;
class pgTextSearchConfiguration;

class dlgTextSearchConfiguration : public dlgTypeProperty
{
public:
    dlgTextSearchConfiguration(pgaFactory *factory, frmMain *frame, pgTextSearchConfiguration *cfg, pgSchema *sch);
    int Go(bool modal);

    void CheckChange();
    wxString GetSql();
    pgObject *CreateObject(pgCollection *collection);
    pgObject *GetObject();

private:
    void OnChange(wxCommandEvent &ev);

    pgSchema *schema;
    pgTextSearchConfiguration *config;
    bool dirtyTokens;

#ifdef __WXMAC__
    void OnChangeSize(wxSizeEvent &ev);
#endif

    void OnSelChangeToken(wxListEvent &ev);
    void OnChangeCbToken(wxCommandEvent &ev);
    void OnChangeTxtDictionary(wxCommandEvent &ev);
    void OnChangeCbDictionary(wxCommandEvent &ev);
    void OnAddToken(wxCommandEvent &ev);
    void OnChangeToken(wxCommandEvent &ev);
    void OnRemoveToken(wxCommandEvent &ev);

    DECLARE_EVENT_TABLE()
};


#endif
