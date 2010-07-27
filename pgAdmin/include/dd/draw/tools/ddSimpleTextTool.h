//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbObject.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbObject.h - 
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDSIMPLETEXTTOOL_H
#define DDSIMPLETEXTTOOL_H

#include "dd/draw/tools/ddFigureTool.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"


class ddSimpleTextTool : public ddFigureTool
{

public:
	ddSimpleTextTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddSimpleTextTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
	virtual void activate();
	virtual void deactivate();
	virtual void mouseDrag(ddMouseEvent& event);
	virtual void OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view);
	//Because a bug it was move to main View class as a hack. virtual void changeHandler(wxCommandEvent& event);
protected:
private:
	ddSimpleTextFigure *txtFigure;
	void calculateSizeEntry(ddDrawingView *view);
	bool showEdit;
	wxTextCtrl *edit;
	wxBitmapButton *okButton, *cancelButton;
	//Because a bug in the way wxwidgets connect events I can't declare it here, wxTextCtrl *edit, instead I do it on the view.
};
#endif
