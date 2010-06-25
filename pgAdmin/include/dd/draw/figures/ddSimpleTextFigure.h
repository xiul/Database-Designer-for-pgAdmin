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

#ifndef DDSIMPLETEXTFIGURE_H
#define DDSIMPLETEXTFIGURE_H
#include "dd/draw/figures/ddAbstractFigure.h"
/*#include "dd/draw/main/ddObject.h"
#include "dd/draw/utilities/ddCollection.h"
#include "dd/draw/handles/ddIHandle.h"
//#include "dd/draw/connectors/ddIConnector.h"
class ddITool;			// HACK-FIX circular reference
class ddDrawingEditor;
class ddIConnector;
class ddITool;
*/

class ddSimpleTextFigure : public ddAbstractFigure
{
public:
	ddSimpleTextFigure(wxString textString);
    ~ddSimpleTextFigure();
	virtual void setText(wxString textString);
	virtual wxString& getText();
	virtual void setEditable(bool value);
	virtual void setFont(wxFont textFont);
	virtual void setForeground(wxColour colour);
	virtual void setBackground(wxBrush background);
	virtual int getPadding();
	void basicMoveBy(int x, int y);
	virtual void basicDraw(wxBufferedDC& context);
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
protected:
	virtual void getFontMetrics(int &width, int &height, wxBufferedDC& context);
	virtual void recalculateDisplayBox(wxBufferedDC& context);
	virtual void setupLayout(wxBufferedDC& context);
private:
	bool textEditable;
	bool refreshDisplayBox;
	int padding;
	wxString text;
	wxFont font;
	wxColour textForeground;
	wxBrush textBackground;

};
#endif
