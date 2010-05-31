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

// App headers
#include "dd/draw/ddIHandle.h"


// Overwrite and disable onEraseBackground Event to avoid Flicker

/*
		#region Properties
		
		IFigure Owner { get; }
		RectangleD DisplayBox { get; }
		double LineWidth { get; set; }
		Cairo.Color FillColor { get; set; }
		Cairo.Color LineColor { get; set; }
		
		#endregion
		
		#region Methods

		bool ContainsPoint (double x, double y);
		void Draw (Context context);
		PointD Locate ();
		void InvokeStart (double x, double y, IDrawingView view);
		void InvokeStep (double x, double y, IDrawingView view);
		void InvokeEnd (double x, double y, IDrawingView view);
		Gdk.Cursor CreateCursor ();
*/