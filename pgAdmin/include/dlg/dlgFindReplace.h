//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgFindReplace.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgFindReplace.h - Search and replace
//
//////////////////////////////////////////////////////////////////////////

#ifndef dlgFindReplace_H
#define dlgFindReplace_H

#include "dlg/dlgClasses.h"

class ctlSQLBox;

// Class declarations
class dlgFindReplace : public pgDialog
{
public:
    dlgFindReplace(ctlSQLBox *parent);
    ~dlgFindReplace();
    void FocusSearch();
    void FindNext();

private:

    void OnClose(wxCloseEvent &ev);
    void OnCancel(wxCommandEvent &ev);
    void OnChange(wxCommandEvent& ev);
    void OnFind(wxCommandEvent& ev);
    void OnReplace(wxCommandEvent& ev);
    void OnReplaceAll(wxCommandEvent& ev);

    ctlSQLBox *sqlbox;

    DECLARE_EVENT_TABLE()
};

#endif
