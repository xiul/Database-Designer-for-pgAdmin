//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: xh_ctlcombo.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// xh_ctlcombo.cpp - ctlComboBox handler
//
//////////////////////////////////////////////////////////////////////////
 
#include "pgAdmin3.h"

#include "wx/wx.h"
#include "ctl/ctlComboBox.h"
#include "ctl/xh_ctlcombo.h"

IMPLEMENT_DYNAMIC_CLASS(ctlComboBoxXmlHandler, wxComboBoxXmlHandler)


wxObject *ctlComboBoxXmlHandler::DoCreateResource()
{ 
    ctlComboBox *ctl=new ctlComboBox(m_parentAsWindow, GetID(), GetPosition(), GetSize(), GetStyle());
    
    SetupWindow(ctl);
   
    return ctl;
}

bool ctlComboBoxXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("ctlComboBox"));
}
