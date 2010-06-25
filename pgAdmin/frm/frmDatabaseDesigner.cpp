#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "frm/frmDatabaseDesigner.h"
#include "ctl/ctlMenuToolbar.h"

// Designer headers
#include "dd/draw/figures/ddAbstractFigure.h"
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/tools/ddSelectionTool.h"
#include "dd/draw/tools/ddDragCreationTool.h"
#include "dd/draw/tools/ddConnectionCreationTool.h"
#include "dd/draw/figures/ddLineConnection.h"

// Icons
#include "images/sql-32.xpm"


/* TODO-DD Fix this and bug when you run this form and close pgAdmin
BEGIN_EVENT_TABLE(frmDatabaseDesigner, pgFrame)
EVT_CLOSE(                      frmDatabaseDesigner::OnClose)
END_EVENT_TABLE()
*/


 frmDatabaseDesigner::frmDatabaseDesigner(frmMain *form, const wxString& _title) //DD-TODO: pgConn *_conn, const wxString& query, const wxString& file)
:pgFrame(NULL, _title)
{
	mainForm=form;
	SetMinSize(wxSize(450,300));
//	view = new ddDrawingView(this,wxSize(800,600),new ddDrawing());
	editor = new ddDrawingEditor(this);
	tool = new ddSelectionTool(editor);
	//DD-TODO: initial tool should be a parameter for editor because it owns and should delete it
	editor->setTool(tool);
	f=new ddAbstractFigure();
	f->displayBox().SetPosition(wxPoint(5,5));
	f->displayBox().width=100;
	f->displayBox().height=100;
	//f->setSelected(false);
	editor->view()->add(f);

	f2=new ddAbstractFigure();
	f2->displayBox().SetPosition(wxPoint(150,150));
	f2->displayBox().width=130;
	f2->displayBox().height=130;
	//f2->setSelected(true);
	editor->view()->add(f2);

	f3=new ddAbstractFigure();
	f3->displayBox().SetPosition(wxPoint(290,290));
	f3->displayBox().width=130;
	f3->displayBox().height=130;
	editor->view()->add(f3);
	
/*

ddPolyLineFigure *f3 = new ddPolyLineFigure();

//Rectangle	
/*		f3->addPoint (10, 10);
			f3->addPoint (60, 10);
			f3->addPoint (60, 60);
			f3->addPoint (10, 60);
			f3->addPoint (10, 10);
//OR
*/	
//Trianglw
			/*f3->addPoint (15, 15);
			f3->addPoint (55, 55);
			f3->addPoint (15, 55);
			f3->addPoint (45, 75);

editor->view()->add(f3);
*/

//antes	editor->setTool(new ddDragCreationTool(editor,f3)); 

ddLineConnection *f4 = new ddLineConnection();
f4->setStartTerminal(new ddLineTerminal());
f4->setEndTerminal(new ddLineTerminal());
editor->setTool(new ddConnectionCreationTool(editor,f4));
	//SetIcon(wxIcon(sql_32_xpm));

ddSimpleTextFigure *f5 = new ddSimpleTextFigure(wxT("preuba"));
f5->displayBox().SetPosition(wxPoint(260,260));
f5->setEditable(true);
editor->view()->add(f5);


}
 frmDatabaseDesigner::~frmDatabaseDesigner(){
//DD-TODO: free memory objects
	 delete editor;
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