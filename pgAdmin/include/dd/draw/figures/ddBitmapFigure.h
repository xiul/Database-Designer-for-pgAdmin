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

#ifndef DDBITMAPFIGURE_H
#define DDBITMAPFIGURE_H

#include "dd/draw/figures/ddAbstractFigure.h"
//#include "dd/draw/utilities/ddCollection.h"
//#include "dd/draw/handles/ddIHandle.h"
//#include "dd/draw/connectors/ddIConnector.h"
//#include "dd/draw/utilities/ddRect.h"

/*class ddITool;			// HACK-FIX circular reference
class ddDrawingEditor;
class ddIConnector;
class ddITool;
*/
class ddBitmapFigure : public ddAbstractFigure
{
public:
	ddBitmapFigure(wxBitmap image);
    ~ddBitmapFigure();

	virtual void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	virtual void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);		
	virtual void changeBitmap(wxBitmap image);
	virtual int getWidth();
	virtual int getHeight();

protected:

private:
	wxBitmap imageToDraw;
};
#endif
