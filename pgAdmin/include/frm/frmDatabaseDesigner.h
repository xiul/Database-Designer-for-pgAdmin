
#ifndef __FRM_DATABASEDESIGNER_H
#define __FRM_DATABASEDESIGNER_H

// Designer headers
#include "dd/draw/main/ddDrawingView.h"
#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/figures/ddAbstractFigure.h"
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/tools/ddSelectionTool.h"
#include "dd/draw/tools/ddDragCreationTool.h"
#include "dd/draw/tools/ddConnectionCreationTool.h"
#include "dd/draw/figures/ddLineConnection.h"

class frmDatabaseDesigner : public pgFrame
{
public:
	frmDatabaseDesigner(frmMain *form, const wxString& _title); //DD-TODO: future include need from this parameters: pgConn *conn, const wxString& qry, const wxString& file = wxEmptyString);
	~frmDatabaseDesigner();
	void Go();
private:
	frmMain *mainForm;
	ddDrawingEditor *editor;
	ddLineConnection *f4;
	ddAbstractFigure *f3,*f2,*f;
	ddITool *tool;
	void OnClose(wxCloseEvent& event);


	wxAuiManager manager;
};

///////////////////////////////////////////////////////

class databaseDesignerBaseFactory : public actionFactory
{
protected:
    databaseDesignerBaseFactory(menuFactoryList *list) : actionFactory(list) {}
    wxWindow *StartDialogDesigner(frmMain *form, pgObject *obj, const wxString &sql);
public:
    bool CheckEnable(pgObject *obj);
};

class databaseDesignerFactory : public databaseDesignerBaseFactory
{
public:
    databaseDesignerFactory(menuFactoryList *list, wxMenu *mnu, ctlMenuToolbar *toolbar);
    wxWindow *StartDialog(frmMain *form, pgObject *obj);
};

#endif // __FRM_DATABASEDESIGNER_H