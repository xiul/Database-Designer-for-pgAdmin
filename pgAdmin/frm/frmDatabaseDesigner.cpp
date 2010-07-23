#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "frm/frmDatabaseDesigner.h"
#include "ctl/ctlMenuToolbar.h"

// Designer headers
#include "dd/dditems/figures/ddColumnKindIcon.h"
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"
//#include "dd/draw/figures/ddCompositeFigure.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/draw/figures/ddRectangleFigure.h"
#include "dd/draw/figures/ddBitmapFigure.h"
#include "dd/draw/tools/ddConnectionCreationTool.h"

#include "dd/ddmodel/ddDatabaseDesign.h"

#include "dd/dditems/figures/ddTextColumnFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/figures/ddTableFigure.h"


//#include "dd/dditems/utilities/ddDataType.h"


// Icons
#include "images/sql-32.xpm"
#include "images/file_new.xpm"
#include "images/help.xpm"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks

/* TODO-DD Fix this and bug when you run this form and close pgAdmin
BEGIN_EVENT_TABLE(frmDatabaseDesigner, pgFrame)
EVT_CLOSE(                      frmDatabaseDesigner::OnClose)
END_EVENT_TABLE()
*/


 frmDatabaseDesigner::frmDatabaseDesigner(frmMain *form, const wxString& _title) //DD-TODO: pgConn *_conn, const wxString& query, const wxString& file)
:pgFrame(NULL, _title)
{

//DD-todo: this is just a development window and SHOULD BE FINISHED IN A FUTURE BUT THIS IS NOT PRIORITY RIGHT NOW
	mainForm=form;

	//RestorePosition(100, 100, 600, 500, 450, 300);
    // notify wxAUI which frame to use
    manager.SetManagedWindow(this);
    manager.SetFlags(wxAUI_MGR_DEFAULT | wxAUI_MGR_TRANSPARENT_DRAG);


	SetMinSize(wxSize(450,300));
	SetSize(wxSize(1024,768));
	wxWindowBase::SetFont(settings->GetSystemFont());

	menuBar = new wxMenuBar();
	wxMenu *helpMenu=new wxMenu();
    helpMenu->Append(MNU_CONTENTS, _("&Help"),                 _("Open the helpfile."));
    helpMenu->Append(MNU_HELP, _("&SQL Help\tF1"),                _("Display help on SQL commands."));

    menuBar->Append(helpMenu, _("&Help"));

	SetMenuBar(menuBar);


	int iWidths[6] = {0, -1, 40, 150, 80, 80};
	wxStatusBar *statusBar =CreateStatusBar(6);
    SetStatusBarPane(-1);
    SetStatusWidths(6, iWidths);
    SetStatusText(_("ready"), STATUSPOS_MSGS);

	
    toolBar = new ctlMenuToolbar(this, -1, wxDefaultPosition, wxDefaultSize, wxTB_FLAT | wxTB_NODIVIDER);

    toolBar->SetToolBitmapSize(wxSize(16, 16));

	toolBar->AddTool(MNU_NEW, _("New"), wxBitmap(file_new_xpm), _("New window"), wxITEM_NORMAL);
	toolBar->AddSeparator();
    toolBar->AddTool(MNU_HELP, _("Help"), wxBitmap(help_xpm), _("Display help on SQL commands."), wxITEM_NORMAL);
    toolBar->Realize();

	wxNotebook *notebook = new wxNotebook(this, CTL_NTBKCENTER, wxDefaultPosition, wxDefaultSize);
	wxSplitterWindow *ddMainContainer = new wxSplitterWindow(notebook,GQB_HORZ_SASH,wxDefaultPosition,wxDefaultSize,wxSP_3D);	
	wxPanel *pnlQuery = new wxPanel(ddMainContainer);
	wxPanel *pnlQuery2 = new wxPanel(notebook);

	design = NULL;
	design = new ddDatabaseDesign(ddMainContainer);
//	tool = new ddSelectionTool(editor);
//	editor->setTool(tool);

	ddMainContainer->SplitVertically(pnlQuery,design->getView());
    ddMainContainer->UpdateSize();
    ddMainContainer->SetSashPosition(50,true);
    ddMainContainer->SetMinimumPaneSize(10);
    ddMainContainer->UpdateSize();

	notebook->AddPage(ddMainContainer, _("Database Designer"));
	notebook->AddPage(pnlQuery2, _("Empty"));
	notebook->SetSelection(0);

	manager.AddPane(notebook, wxAuiPaneInfo().Name(wxT("sqlQuery")).Caption(_("Database Designer")).Center().CaptionVisible(false).CloseButton(false).MinSize(wxSize(200,100)).BestSize(wxSize(350,200)));
	manager.AddPane(toolBar, wxAuiPaneInfo().Name(wxT("toolBar")).Caption(_("Tool bar")).ToolbarPane().Top().LeftDockable(false).RightDockable(false));

	manager.Update();


//*****************************************************************************************************
//		TEST DATA
//*****************************************************************************************************

/*

	f=new ddRectangleFigure();
	f->displayBox().SetPosition(wxPoint(5,5));
	f->displayBox().width=100;
	f->displayBox().height=100;
	//f->setSelected(false);
	design->addTable(f);

	f2=new ddRectangleFigure();
	f2->displayBox().SetPosition(wxPoint(150,150));
	f2->displayBox().width=130;
	f2->displayBox().height=130;
	//f2->setSelected(true);
	design->addTable(f2);

	f3=new ddRectangleFigure();
	f3->displayBox().SetPosition(wxPoint(290,290));
	f3->displayBox().width=130;
	f3->displayBox().height=130;
	design->addTable(f3);
	

//ddPolyLineFigure *f3 = new ddPolyLineFigure();
//Rectangle	
//		f3->addPoint (10, 10);
//			f3->addPoint (60, 10);
//			f3->addPoint (60, 60);
//			f3->addPoint (10, 60);
//			f3->addPoint (10, 10);
//OR
//	
//Trianglw
//			f3->addPoint (15, 15);
//			f3->addPoint (55, 55);
//			f3->addPoint (15, 55);
//			f3->addPoint (45, 75);
//
//editor->view()->add(f3);
//antes	editor->setTool(new ddDragCreationTool(editor,f3)); 

/*ddLineConnection *f4 = new ddLineConnection();
f4->setStartTerminal(new ddLineTerminal());
f4->setEndTerminal(new ddLineTerminal());
//design->setTool(new ddConnectionCreationTool(design->getEditor(),f4));
	//SetIcon(wxIcon(sql_32_xpm));
*/
/*
ddSimpleTextFigure *f5 = new ddSimpleTextFigure(wxString(wxT("Texto Solito")));
f5->displayBox().SetPosition(wxPoint(60,60));
f5->setEditable(true);
design->addTable(f5);
*/

ddColumnFigure *f61 = new ddColumnFigure(wxString(wxT("Id")));
f61->displayBox().SetPosition(wxPoint(260,270));
//f61->setEditable(true);

ddColumnFigure *f62 = new ddColumnFigure(wxString(wxT("SomeValue")));
f62->displayBox().SetPosition(wxPoint(260,290));
//f62->setEditable(true);

ddTableFigure *f6 = new ddTableFigure(225,225);
f6->addColumn(f62);
f6->addColumn(f61);
design->addTable(f6);


ddColumnFigure *f71 = new ddColumnFigure(wxString(wxT("Id")));
f71->displayBox().SetPosition(wxPoint(260,270));
//f71->setEditable(true);

ddColumnFigure *f72 = new ddColumnFigure(wxString(wxT("Amount")));
f72->displayBox().SetPosition(wxPoint(260,290));
//f72->setEditable(true);

ddTableFigure *f7 = new ddTableFigure(100,100);
f7->addColumn(f72);
f7->addColumn(f71);
design->addTable(f7);



ddTableFigure *f8 = new ddTableFigure(350,100);
design->addTable(f8);

ddColumnFigure *f9 = new ddColumnFigure(wxString(wxT("Id")));
f9->moveTo(444,444);
//6666 fix this, if you move displaybox then figures should be moved
//f9->setEditable(true);
design->addTable(f9);

ddColumnKindIcon *f10 = new ddColumnKindIcon();
f10->displayBox().SetPosition(wxPoint(120,120));
f10->displayBox().SetSize(wxSize(50,50));
design->addTable(f10);
}

 frmDatabaseDesigner::~frmDatabaseDesigner(){
	//DD-TODO: free memory objects
	//closing = true;
	// Uninitialize wxAUIManager
	manager.UnInit();
	
	if(design)
		delete design;
		
	if (mainForm)
		mainForm->RemoveFrame(this);
 }

void frmDatabaseDesigner::Go()
{
    /*cbConnection->SetSelection(0L);
    wxCommandEvent ev;
    OnChangeConnection(ev);
	*/

    Show(true);
    //sqlQuery->SetFocus();
    //loading = false;
}


void frmDatabaseDesigner::OnClose(wxCloseEvent& event)
{
    /* if (queryMenu->IsEnabled(MNU_CANCEL))
    {
        if (event.CanVeto())
        {
            wxMessageDialog msg(this, _("A query is running. Do you wish to cancel it?"), _("Query"),
                wxYES_NO|wxNO_DEFAULT|wxICON_EXCLAMATION);

            if (msg.ShowModal() == wxID_NO)
            {
                event.Veto();
                return;
            }
        }

        wxCommandEvent ev;
        OnCancel(ev);
    }

    while (sqlResult->RunStatus() == CTLSQL_RUNNING)
    {
        wxLogInfo(wxT("SQL Query box: Waiting for query to abort"));
        wxSleep(1);
    }

    if (CheckChanged(event.CanVeto()) && event.CanVeto())
    {
        event.Veto();
        return;
    }

    closing = true;

    // Reset the panes
    if (viewMenu->IsChecked(MNU_OUTPUTPANE))
        manager.GetPane(wxT("outputPane")).Show(true);
    if (viewMenu->IsChecked(MNU_SCRATCHPAD))
        manager.GetPane(wxT("scratchPad")).Show(true);
    manager.Update();

    Hide();

    sqlQuery->Disconnect(wxID_ANY, wxEVT_SET_FOCUS,wxFocusEventHandler(frmQuery::OnFocus));
    sqlResult->Disconnect(wxID_ANY, wxEVT_SET_FOCUS, wxFocusEventHandler(frmQuery::OnFocus));
    msgResult->Disconnect(wxID_ANY, wxEVT_SET_FOCUS, wxFocusEventHandler(frmQuery::OnFocus));
    msgHistory->Disconnect(wxID_ANY, wxEVT_SET_FOCUS, wxFocusEventHandler(frmQuery::OnFocus));
    
    controller->nullView();                   //to avoid bug on *nix when deleting controller

    settings->SetExplainVerbose(queryMenu->IsChecked(MNU_VERBOSE));
    settings->SetExplainCosts(queryMenu->IsChecked(MNU_COSTS));
    settings->SetExplainBuffers(queryMenu->IsChecked(MNU_BUFFERS));

    sqlResult->Abort();                           // to make sure conn is unused

    Destroy();
*/
	Hide();
	Destroy();
}


 ///////////////////////////////////////////////////////

 bool databaseDesignerBaseFactory::CheckEnable(pgObject *obj)
{
    return obj && obj->GetDatabase() && obj->GetDatabase()->GetConnected();
}

wxWindow *databaseDesignerBaseFactory::StartDialogDesigner(frmMain *form, pgObject *obj, const wxString &sql)
{
    pgDatabase *db=obj->GetDatabase();
    wxString applicationname = wxT("pgAdmin - Database Designer");
    pgConn *conn = db->CreateConn(applicationname);
    if (conn)
    {
        frmDatabaseDesigner *fd= new frmDatabaseDesigner(form, wxEmptyString); //, conn, sql);
        fd->Go();
        return fd;
    }
    return 0;
}

databaseDesignerFactory::databaseDesignerFactory(menuFactoryList *list, wxMenu *mnu, ctlMenuToolbar *toolbar) : databaseDesignerBaseFactory(list)
{
    //TODO: complete this Ctrl-D by example isn't bind with keys.
	mnu->Append(id, _("&Database Designer\tCtrl-D"), _("Create physical database designs."));
    toolbar->AddTool(id, _("Database Designer\tCtrl-D"), wxBitmap(sql_32_xpm), _("Create physical database designs."), wxITEM_NORMAL);
}

wxWindow *databaseDesignerFactory::StartDialog(frmMain *form, pgObject *obj)
{
    wxString qry;
    if (settings->GetStickySql())
        qry = obj->GetSql(form->GetBrowser());
    return StartDialogDesigner(form, obj, qry);
}