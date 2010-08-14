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
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"
/*#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/handles/ddIHandle.h"
*/

class ddRelationshipItem;

WX_DECLARE_STRING_HASH_MAP( ddRelationshipItem*, columnsHashMap );


class ddRelationshipFigure : public ddLineConnection
{
public:
	ddRelationshipFigure();
	ddRelationshipFigure(ddIFigure *figure1, ddIFigure *figure2);
	~ddRelationshipFigure();
	void updateForeignKey();
	void removeForeignKeys();
	bool getIdentifying();
	bool getOneToMany();
	bool getMandatory();
	void setOptionAtForeignKeys(ddColumnOptionType type);
	void setKindAtForeignKeys(ddColumnType type);
	virtual void connectEnd(ddIConnector *end);
	virtual void connectStart(ddIConnector *start);
	void disconnectStart();
	void disconnectEnd();
	//bool belongsToThisTable(ddTableFigure *possibleOwner);
	wxString generateSQL();
protected:
/*	virtual void connectFigure (ddIConnector *connector);
	virtual void disconnectFigure (ddIConnector *connector);
	*/
private:
	virtual wxArrayString& popupStrings();
	virtual void OnTextPopupClick(wxCommandEvent& event, ddDrawingView *view);
	wxArrayString strings;
	bool fkFromPk;
	bool fkMandatory;
	bool fkOneToMany;
	bool fkIdentifying;
	int ukIndex;
	columnsHashMap chm;
	ddTableFigure *disconnectedEndTable;
};



class ddRelationshipItem : public ddObject
{
public:
	ddRelationshipItem(ddColumnFigure *originalColumn, ddTableFigure *destination, ddColumnOptionType type, ddColumnType colType);
	~ddRelationshipItem();
	ddColumnFigure *original;
	ddColumnFigure *fkColumn;
	ddTableFigure *destinationTable;
};

#endif
