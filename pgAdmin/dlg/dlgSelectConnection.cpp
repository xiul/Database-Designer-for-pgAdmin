//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: dlgSelectConnection.cpp 8299 2010-04-26 21:42:34Z guillaume $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// dlgSelectConnection.cpp - Connect to a database
//
//////////////////////////////////////////////////////////////////////////

// App headers
#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/bmpcbox.h>

// App headers
#include "frm/frmMain.h"
#include "dlg/dlgSelectConnection.h"
#include "dlg/dlgConnect.h"
#include "schema/pgServer.h"
#include "images/connect.xpm"

#define CTRLID_CBSERVER 4242
#define CTRLID_CBDATABASE 4243

BEGIN_EVENT_TABLE(dlgSelectConnection, DialogWithHelp)
    EVT_COMBOBOX(CTRLID_CBSERVER,      dlgSelectConnection::OnChangeServer) 
    EVT_COMBOBOX(CTRLID_CBDATABASE,    dlgSelectConnection::OnChangeDatabase) 
	EVT_TEXT(CTRLID_CBSERVER,          dlgSelectConnection::OnTextChange)
	EVT_TEXT(CTRLID_CBDATABASE,        dlgSelectConnection::OnTextChange)
	EVT_TEXT(XRCID("cbUsername"),      dlgSelectConnection::OnTextChange)
    EVT_BUTTON (wxID_OK,               dlgSelectConnection::OnOK)
    EVT_BUTTON (wxID_CANCEL,           dlgSelectConnection::OnCancel)
END_EVENT_TABLE()

#define stUsername		CTRL_STATIC("stUsername")
#define cbUsername		CTRL_COMBOBOX("cbUsername")



dlgSelectConnection::dlgSelectConnection(wxWindow *parent, frmMain *form) : 
DialogWithHelp(form)
{
 	remoteServer = NULL;

    wxWindowBase::SetFont(settings->GetSystemFont());
    LoadResource(parent, wxT("dlgSelectConnection"));

    SetIcon(wxIcon(connect_xpm));
    RestorePosition();

	cbServer = new ctlComboBoxFix(this, CTRLID_CBSERVER, ConvertDialogToPixels(wxPoint(65,5)), ConvertDialogToPixels(wxSize(135,12)), wxCB_DROPDOWN | wxCB_READONLY);
	cbDatabase = new wxComboBox(this, CTRLID_CBDATABASE, wxEmptyString, ConvertDialogToPixels(wxPoint(65,20)), ConvertDialogToPixels(wxSize(135,12)), NULL, wxCB_DROPDOWN | wxCB_READONLY);

	if (form == NULL)
	{
		cbServer->SetValue(settings->Read(wxT("QuickConnect/server"), wxEmptyString));
		cbDatabase->SetValue(settings->Read(wxT("QuickConnect/database"), wxEmptyString));
		cbUsername->SetValue(settings->Read(wxT("QuickConnect/username"), wxEmptyString));
	}

	btnOK->Enable(cbServer->GetValue().Length() > 0 && cbDatabase->GetValue().Length() > 0 && cbUsername->GetValue().Length() > 0);
}


dlgSelectConnection::~dlgSelectConnection()
{
    SavePosition();
}


wxString dlgSelectConnection::GetHelpPage() const
{
    return wxT("connect");
}


void dlgSelectConnection::OnChangeServer(wxCommandEvent& ev)
{
	if (!GetServer())
		return;

    cbDatabase->Clear();

    int sel=cbServer->GetCurrentSelection();
    if (sel >= 0)
    {
        remoteServer = (pgServer*)cbServer->GetClientData(sel);

        if (!remoteServer->GetConnected())
        {
            remoteServer->Connect(mainForm, remoteServer->GetStorePwd());
            if (!remoteServer->GetConnected())
            {
                wxLogError(wxT("%s"), remoteServer->GetLastError().c_str());
                return;
            }
        }
        if (remoteServer->GetConnected())
        {
            pgSetIterator set1(remoteServer->GetConnection(), 
                wxT("SELECT DISTINCT datname\n")
                wxT("  FROM pg_database db\n")
                wxT(" WHERE datallowconn ORDER BY datname"));

            while(set1.RowsLeft())
                cbDatabase->Append(set1.GetVal(wxT("datname")));

            if (cbDatabase->GetCount())
                cbDatabase->SetSelection(0);

            pgSetIterator set2(remoteServer->GetConnection(), 
                wxT("SELECT DISTINCT usename\n")
                wxT("FROM pg_user db\n")
                wxT("ORDER BY usename"));

            while(set2.RowsLeft())
                cbUsername->Append(set2.GetVal(wxT("usename")));

            if (cbUsername->GetCount())
                cbUsername->SetSelection(0);
        }

    }
    OnChangeDatabase(ev);
}


wxString dlgSelectConnection::GetDatabase()
{
    return cbDatabase->GetValue();
}

wxString dlgSelectConnection::GetServerName()
{
	return cbServer->GetValue();
}

void dlgSelectConnection::OnChangeDatabase(wxCommandEvent& ev)
{
	btnOK->Enable(cbServer->GetValue().Length() > 0 && cbDatabase->GetValue().Length() > 0 && cbUsername->GetValue().Length() > 0);
}

void dlgSelectConnection::OnTextChange(wxCommandEvent& ev)
{
	btnOK->Enable(cbServer->GetValue().Length() > 0 && cbDatabase->GetValue().Length() > 0 && cbUsername->GetValue().Length() > 0);
}

void dlgSelectConnection::OnOK(wxCommandEvent& ev)
{
#ifdef __WXGTK__
    if (!btnOK->IsEnabled())
        return;
#endif

	if (cbDatabase->GetCurrentSelection() == wxNOT_FOUND ||
		cbServer->GetCurrentSelection() == wxNOT_FOUND)
		remoteServer = NULL;

    EndModal(wxID_OK);
}


void dlgSelectConnection::OnCancel(wxCommandEvent& ev)
{
    EndModal(wxID_CANCEL);
}

pgConn *dlgSelectConnection::CreateConn(wxString& applicationname)
{
    /* gcc requires that we store this in temporary variables for some reason... */
    wxString serv = cbServer->GetValue();
    wxString db = cbDatabase->GetValue();

	long port = 0;
	if (serv.Find(':') > 0)
	{
		if (!serv.Mid(serv.Find(':')+1).ToLong(&port))
		{
			wxMessageBox(_("Invalid port number specified."));
			return NULL;
		}
		serv = serv.Mid(0, serv.Find(':'));
	}

    wxString user = cbUsername->GetValue();

	return CreateConn(serv, db, user, port, 0, applicationname, true);
}

pgConn *dlgSelectConnection::CreateConn(wxString& server, wxString& dbname, wxString& username, int port, int sslmode, wxString& applicationname, bool writeMRU)
{
	pgConn *newconn;
	newconn = new pgConn(server, dbname, username, wxT(""), port, sslmode, 0, applicationname);
	if (newconn->GetStatus() != PGCONN_OK &&
		newconn->GetLastError().Cmp(wxString(PQnoPasswordSupplied, wxConvUTF8)) == 0)
	{
		/* Needs password */
		delete newconn;
		newconn = NULL;

        wxString txt;
        txt.Printf(_("Please enter password for user %s\non server %s"), username.c_str(), server.c_str());
		dlgConnect dlg(NULL, txt, false);
		if (dlg.Go() != wxID_OK)
			return NULL;

		newconn = new pgConn(server, dbname, username, dlg.GetPassword(), port, sslmode, 0, applicationname);
	}

	if (newconn)
	{
		if (newconn->GetStatus() != PGCONN_OK)
		{
			wxMessageBox(wxT("Connection failed: ") + newconn->GetLastError());
			return NULL;
		}

		if (writeMRU)
		{
			settings->Write(wxT("QuickConnect/server"), cbServer->GetValue());
			settings->Write(wxT("QuickConnect/database"), cbDatabase->GetValue());
			settings->Write(wxT("QuickConnect/username"), cbUsername->GetValue());
		}
	}
	return newconn;
}

int dlgSelectConnection::Go(pgConn *conn, wxBitmapComboBox *cb)
{
    cbConnection=cb;
	if (mainForm != NULL)
	{
        ctlTree *browser = mainForm->GetBrowser();
        wxTreeItemIdValue foldercookie, servercookie;
        wxTreeItemId folderitem, serveritem;
        pgObject *object;
        pgServer *server;

        folderitem = browser->GetFirstChild(browser->GetRootItem(), foldercookie);
        while (folderitem)
        {
            if (browser->ItemHasChildren(folderitem))
            {
                serveritem = browser->GetFirstChild(folderitem, servercookie);
                while (serveritem)
                {
                    object = browser->GetObject(serveritem);
                    if (object->IsCreatedBy(serverFactory))
                    {
                        server = (pgServer *)object;
			            cbServer->Append(server->GetIdentifier(), (void*)server);
			            if (server->GetConnected() &&
                            server->GetConnection()->GetHost() == conn->GetHost() &&
                            server->GetConnection()->GetPort() == conn->GetPort())
			            {
			            	 cbServer->SetSelection(cbServer->GetCount()-1);
			            	 remoteServer = server;
			            }
                    }
                    serveritem = browser->GetNextChild(folderitem, servercookie);
                }
            }
            folderitem = browser->GetNextChild(browser->GetRootItem(), foldercookie);
        }
		cbServer->SetFocus();
	}

    wxCommandEvent ev;
    OnChangeServer(ev);

    return ShowModal();
}

