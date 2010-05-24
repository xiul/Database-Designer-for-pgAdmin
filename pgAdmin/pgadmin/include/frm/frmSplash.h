//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: frmSplash.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// frmSplash.h - Splash Screen
//
//////////////////////////////////////////////////////////////////////////

#ifndef SPLASH_H
#define SPLASH_H

// Class declarations
class frmSplash : public wxFrame
{
public:
    frmSplash(wxFrame *parent);
    void OnPaint(wxPaintEvent&);
    
private:
    void SetWindowShape();
    void OnWindowCreate(wxWindowCreateEvent& WXUNUSED(evt));

    wxBitmap splash;
    DECLARE_EVENT_TABLE()
};

#endif
