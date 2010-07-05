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

#ifndef DDRECTANGLEFIGURE_H
#define DDRECTANGLEFIGURE_H

#include <wx/dcbuffer.h>

#include "dd/draw/figures/ddAbstractFigure.h"


class ddDrawingView;

class ddRectangleFigure : public ddAbstractFigure
{
public:
	ddRectangleFigure();
    ~ddRectangleFigure();
	void basicDraw(wxBufferedDC& context, ddDrawingView *view);
	void basicDrawSelected(wxBufferedDC& context, ddDrawingView *view);
	void setRectangle(ddRect& rect);
	void setSize(wxSize& size);

protected:
private:
};
#endif
