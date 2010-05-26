//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: xh_ctltree.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// xh_ctltree.h - ctlTree handler
//
//////////////////////////////////////////////////////////////////////////


#ifndef _WX_XH_CTLTREE_H_
#define _WX_XH_CTLTREE_H_

#include "wx/xrc/xmlres.h"
#include "wx/xrc/xh_tree.h"

//class WXDLLIMPEXP_XRC 
class ctlTreeXmlHandler : public wxTreeCtrlXmlHandler
{
DECLARE_DYNAMIC_CLASS(ctlTreeXmlHandler)
public:
    ctlTreeXmlHandler() : wxTreeCtrlXmlHandler() {}
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};


#endif 
