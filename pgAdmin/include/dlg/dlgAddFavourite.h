//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgAddFavourite.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgAddFavourite.h - Add a favourite
//
//////////////////////////////////////////////////////////////////////////

#ifndef dlgAddFavourite_H
#define dlgAddFavourite_H

#include "dlg/dlgClasses.h"
#include "utils/favourites.h"

// Class declarations
class dlgAddFavourite : public pgDialog
{
public:
    dlgAddFavourite(wxWindow *parent, queryFavouriteFolder *favourites);
    ~dlgAddFavourite();
	bool AddFavourite(wxString newtext);
    
private:
	queryFavouriteFolder *favourites;
    void OnOK(wxCommandEvent& ev);
    void OnCancel(wxCommandEvent& ev);
	void OnChange(wxCommandEvent &ev);
	void OnTreeChange(wxTreeEvent &ev);
    DECLARE_EVENT_TABLE()
};

#endif
