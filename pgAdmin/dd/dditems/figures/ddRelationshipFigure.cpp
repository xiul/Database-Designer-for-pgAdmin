//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawing.cpp - Container for figures that send changed events to Listeners whenever 
//	a part of its area was invalidated. Using the design pattern observer to decouple the
//	Drawing from its views and to enable multiple views .
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/dcbuffer.h>

// App headers
#include "dd/dditems/figures/ddRelationshipFigure.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddRelationshipFigure::ddRelationshipFigure():
ddLineConnection()
{
	fkColumns = new ddCollection(new ddArrayCollection());
}

ddRelationshipFigure::ddRelationshipFigure(ddIFigure *figure1, ddIFigure *figure2):
ddLineConnection(figure1,figure2)
{
	fkColumns = new ddCollection(new ddArrayCollection());
}

ddRelationshipFigure::~ddRelationshipFigure()
{
	if(fkColumns)
	{
		fkColumns->removeAll();
		delete fkColumns;
	}
}

void ddRelationshipFigure::addFkColumn(ddColumnFigure *column)
{
	fkColumns->addItem(column);
}

void ddRelationshipFigure::removeFkColumn(wxString columnName)
{
/*	ddIteratorBase *iterator=figuresEnumerator();
	ddColumnFigure *c;
	while(iterator->HasNext()){
		c = (ddColumnFigure *) iterator->Next();
		c->
	}	
	delete iterator;

	fkColumns->removeItem(column);
*/
}