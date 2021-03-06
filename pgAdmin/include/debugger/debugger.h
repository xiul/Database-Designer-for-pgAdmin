//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: debugger.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// debugger.h - Debugger factories
//
//////////////////////////////////////////////////////////////////////////

#ifndef DEBUGGER_H
#define DEBUGGER_H

// wxWindows headers
#include <wx/wx.h>

///////////////////////////////////////////////////
// Debugger factory
///////////////////////////////////////////////////
class debuggerFactory : public actionFactory
{
public:
    debuggerFactory(menuFactoryList *list, wxMenu *mnu, ctlMenuToolbar *toolbar);
    wxWindow *StartDialog(frmMain *form, pgObject *obj);
    bool CheckEnable(pgObject *obj);
};

///////////////////////////////////////////////////
// Breakpoint factory
///////////////////////////////////////////////////
class breakpointFactory : public actionFactory
{
public:
    breakpointFactory(menuFactoryList *list, wxMenu *mnu, ctlMenuToolbar *toolbar);
    wxWindow *StartDialog(frmMain *form, pgObject *obj);
    bool CheckEnable(pgObject *obj);
};

#endif


