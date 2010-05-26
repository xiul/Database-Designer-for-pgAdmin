//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgLanguage.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgLanguage.h - Language property
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_LANGUAGEPROP
#define __DLG_LANGUAGEPROP

#include "dlg/dlgProperty.h"

class pgLanguage;

class dlgLanguage : public dlgSecurityProperty
{
public:
    dlgLanguage(pgaFactory *factory, frmMain *frame, pgLanguage *db);
    int Go(bool modal);

    void CheckChange();
    wxString GetSql();
    pgObject *CreateObject(pgCollection *collection);
    pgObject *GetObject();

private:
    pgLanguage *language;
    void OnChangeName(wxCommandEvent &ev);
#ifdef __WXMAC__
    void OnChangeSize(wxSizeEvent &ev);
#endif

    DECLARE_EVENT_TABLE()
};


#endif
