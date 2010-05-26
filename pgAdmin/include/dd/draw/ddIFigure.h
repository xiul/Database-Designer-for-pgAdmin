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

// Create Array Objects used as base for gqbCollections
class ddIFigure : public ddObject
{
public:
	ddIFigure();
    ~ddIFigure();

	virtual ddRect* DisplayBox() {return new ddRect();};
	virtual bool ContainsPoint (wxPoint point);

	/*
		virtual void AddDependentFigure (ddIFigure figure);
		bool ContainsPoint (double x, double y);
		IConnector ConnectorAt (double x, double y);
		ITool CreateFigureTool (IDrawingEditor editor, ITool defaultTool);
		void Draw (Context context);
		void DrawSelected (Context context);
		object GetAttribute (FigureAttribute attribute);
		bool Includes (IFigure figure);
		void Invalidate ();		
		void MoveBy (double x, double y);
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

private:
	ddRect rect;
	ddCollection *figures;
	ddCollection *handles;
	ddCollection *dependentFigures;
};
#endif
