//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: xh_calb.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// xh_calb.h - wxCalendarBox handler
//
//////////////////////////////////////////////////////////////////////////


#ifndef _WX_XH_CALB_H_
#define _WX_XH_CALB_H_


#include "wx/xrc/xmlres.h"

//class WXDLLIMPEXP_XRC 
class wxCalendarBoxXmlHandler : public wxXmlResourceHandler
{
DECLARE_DYNAMIC_CLASS(wxCalendarBoxXmlHandler)
public:
    wxCalendarBoxXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};


#endif // _WX_XH_CALB_H_
