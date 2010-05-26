//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgTextSearchDictionary.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgTextSearchDictionary.h - Text Search Dictionary property 
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_TSDICTIONARYPROP
#define __DLG_TSDICTIONARYPROP

#include "dlg/dlgProperty.h"

class pgSchema;
class pgTextSearchDictionary;

class dlgTextSearchDictionary : public dlgTypeProperty
{
public:
    dlgTextSearchDictionary(pgaFactory *factory, frmMain *frame, pgTextSearchDictionary *cfg, pgSchema *sch);
    int Go(bool modal);

    void CheckChange();
    wxString GetSql();
    pgObject *CreateObject(pgCollection *collection);
    pgObject *GetObject();

private:
    void OnChange(wxCommandEvent &ev);

    pgSchema *schema;
    pgTextSearchDictionary *dict;

    wxString GetOptionsSql();

#ifdef __WXMAC__
    void OnChangeSize(wxSizeEvent &ev);
#endif

    void OnSelChangeOption(wxListEvent &ev);
    void OnChangeOptionName(wxCommandEvent &ev);
    void OnAddOption(wxCommandEvent &ev);
    void OnChangeOption(wxCommandEvent &ev);
    void OnRemoveOption(wxCommandEvent &ev);

    DECLARE_EVENT_TABLE()
};


#endif
