//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgConnect.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgConnect.h - Connect to a database
//
//////////////////////////////////////////////////////////////////////////

#ifndef DLGCONNECT_H
#define DLGCONNECT_H

#include "dlg/dlgClasses.h"

// Class declarations
class dlgConnect : public DialogWithHelp
{
public:
    dlgConnect(frmMain *form, const wxString& description, bool needPwd);
    ~dlgConnect();
    wxString GetHelpPage() const;


    wxString GetPassword();
    bool GetStorePwd();
    int Go();
    
private:
    void OnOK(wxCommandEvent& ev);
    void OnCancel(wxCommandEvent& ev);
    DECLARE_EVENT_TABLE()
};

#endif
