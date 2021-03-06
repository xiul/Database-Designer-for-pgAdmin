//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: xh_timespin.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// xh_timespin.h - wxTimeSpinCtrl handler
//
//////////////////////////////////////////////////////////////////////////


#ifndef _WX_XH_TIMESPIN_H_
#define _WX_XH_TIMESPIN_H_


#include "wx/xrc/xmlres.h"

//class WXDLLIMPEXP_XRC 
class wxTimeSpinXmlHandler : public wxXmlResourceHandler
{
DECLARE_DYNAMIC_CLASS(wxTimeSpinXmlHandler)
public:
    wxTimeSpinXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};


#endif // _WX_XH_TIMESPIN_H_
