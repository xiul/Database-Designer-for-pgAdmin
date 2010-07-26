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

#ifndef DDCOLUMNTEXTTOOL_H
#define DDCOLUMNTEXTTOOL_H

#include "dd/draw/tools/ddSimpleTextTool.h"
#include "dd/dditems/figures/ddTextColumnFigure.h"


class ddColumnTextTool : public ddSimpleTextTool
{

public:
	ddColumnTextTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt);
    ~ddColumnTextTool();
	virtual void mouseDown(ddMouseEvent& event);  //Mouse Right Click
//	virtual void activate();
//	virtual void deactivate();
//	virtual void mouseDrag(ddMouseEvent& event);
//	virtual void OnTextPopupClick(wxCommandEvent& event);
	//Because a bug it was move to main View class as a hack. virtual void changeHandler(wxCommandEvent& event);
protected:
private:
	ddTextColumnFigure *colTextFigure;
/*	void calculateSizeEntry();
	bool showEdit;
	ddSimpleTextFigure *txtFigure;
	wxTextCtrl *edit;
	//Because a bug in the way wxwidgets connect events I can't declare it here, wxTextCtrl *edit, instead I do it on the view.
*/
};
#endif
