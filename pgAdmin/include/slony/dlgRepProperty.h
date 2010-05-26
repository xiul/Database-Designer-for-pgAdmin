//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgRepProperty.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgRepSet.h - Slony-I property
//
//////////////////////////////////////////////////////////////////////////


#ifndef __DLG_REPPROP
#define __DLG_REPPROP

#include "dlg/dlgProperty.h"

class slCluster;

class dlgRepProperty : public dlgProperty
{
public:
    dlgRepProperty(pgaFactory *f, frmMain *frame, slCluster *c, const wxString &resName);

protected:
    slCluster *cluster;
};


#endif
