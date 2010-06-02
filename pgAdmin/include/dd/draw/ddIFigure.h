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

#ifndef DDIFIGURE_H
#define DDIFIGURE_H
#include "dd/draw/ddRect.h"
#include "dd/draw/ddObject.h"
#include "dd/draw/ddCollection.h"
#include "dd/draw/ddIHandle.h"


class ddITool;			// HACK-FIX circular reference
class ddDrawingEditor;

// Create Array Objects used as base for gqbCollections
class ddIFigure : public ddObject
{
public:
	ddIFigure();
    ~ddIFigure();

	virtual ddRect& displayBox();
	virtual void draw (wxBufferedDC& context);
	virtual void drawSelected (wxBufferedDC& context);
	virtual ddCollection* handlesEnumerator();
	virtual void addDependentFigure (ddIFigure *figure);
	virtual void removeDependentFigure (ddIFigure *figure);
	virtual void addHandle (ddIHandle *handle);
	virtual void removeHandle (ddIHandle *handle);
	virtual void moveBy(int x, int y);
	virtual void moveTo(int x, int y);
	virtual bool containsPoint(int x, int y);
	virtual bool isSelected();
	virtual void setSelected(bool value);
	
	virtual ddITool* CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool);
	/*
		virtual void AddDependentFigure (ddIFigure figure);
		bool ContainsPoint (double x, double y);
		IConnector ConnectorAt (double x, double y);
		
		
		
		object GetAttribute (FigureAttribute attribute);
		bool Includes (IFigure figure);
		void Invalidate ();		
		
		void MoveTo (double x, double y);
		void RemoveDependentFigure (IFigure figure);
		void SetAttribute (FigureAttribute attribute, object value);
		void Visit (IFigureVisitor visitor);	
*/
	
/*
		RectangleD DisplayBox { get; set; }
		IEnumerable <IFigure> FiguresEnumerator { get; }
		IEnumerable <IHandle> HandlesEnumerator { get; }
		IEnumerable <IFigure> DependentFiguresEnumerator { get;	}
		bool CanConnect { get; }

*/	
protected:
	ddRect baseDisplayBox;
	ddCollection *figures;
	ddCollection *handles;
	ddCollection *dependentFigures;
private:
	bool selected;
};
#endif
