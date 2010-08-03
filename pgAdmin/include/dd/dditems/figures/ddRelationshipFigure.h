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

#ifndef DDRELATIONSHIPFIGURE_H
#define DDRELATIONSHIPFIGURE_H
#include "dd/draw/figures/ddLineConnection.h"
//#include "dd/draw/figures/ddIConnectionFigure.h"
/*#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/handles/ddIHandle.h"
*/


class ddRelationshipFigure : public ddLineConnection
{
public:
	ddRelationshipFigure();
	ddRelationshipFigure(ddIFigure *figure1, ddIFigure *figure2);
	~ddRelationshipFigure();

};
#endif
