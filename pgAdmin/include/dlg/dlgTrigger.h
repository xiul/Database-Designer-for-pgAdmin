//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgTrigger.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgTrigger.h - Trigger property 
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_TRIGGERPROP
#define __DLG_TRIGGERPROP

#include "dlg/dlgProperty.h"

class pgTrigger;
class pgTable;

class dlgTrigger : public dlgCollistProperty
{
public:
    dlgTrigger(pgaFactory *factory, frmMain *frame, pgTrigger *trg, pgTable *sch);
    int Go(bool modal);

    void CheckChange();
    wxString GetSql();
    pgObject *CreateObject(pgCollection *collection);
    pgObject *GetObject();
    void SetObject(pgObject *obj) { trigger = (pgTrigger*)obj; }
    wxString GetColumns();


private:
    pgTable *table;
    pgTrigger *trigger;

    void OnChange(wxCommandEvent &ev);
    void OnChangeFunc(wxCommandEvent &ev);
    void OnSelectComboCol(wxCommandEvent &ev);
    void OnSelectListCol(wxListEvent &ev);
    void OnSelectCol();
    void OnAddCol(wxCommandEvent &ev);
    void OnRemoveCol(wxCommandEvent &ev);

	virtual bool IsUpToDate();

    DECLARE_EVENT_TABLE()
};

#endif
