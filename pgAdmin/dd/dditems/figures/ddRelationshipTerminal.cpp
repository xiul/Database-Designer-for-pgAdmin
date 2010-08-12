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
#include "dd/dditems/figures/ddRelationshipTerminal.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/draw/utilities/ddGeometry.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddRelationshipTerminal::ddRelationshipTerminal(ddRelationshipFigure *owner, bool endFigureTerminal){
	//lineDistance = 8;
	//pointDistance = 22;
	ownerFigure = owner;
	endTerminal = endFigureTerminal;

}

ddRelationshipTerminal::~ddRelationshipTerminal(){

}

//DD-TODO: this need this ddDrawingView *view ??? or just avoid this and always pass calcscrolled points
ddPoint& ddRelationshipTerminal::draw (wxBufferedDC& context, ddPoint& a, ddPoint& b, ddDrawingView *view){

	ddGeometry g;
	ddPoint points[3];

	context.SetPen(terminalLinePen);
	
	ddPoint aCopy=a,bCopy=b;
	view->CalcScrolledPosition(aCopy.x,aCopy.y,&aCopy.x,&aCopy.y);
	view->CalcScrolledPosition(bCopy.x,bCopy.y,&bCopy.x,&bCopy.y);



	if(endTerminal){
		//Calc a point very far away of center of table to intersect one of the sides lines of the table rectangle figure
		double X = aCopy.x + (bCopy.x - aCopy.x) * 0.9;
		double Y = aCopy.y + (bCopy.y - aCopy.y) * 0.9;
		
		if(ownerFigure->getEndFigure() && ownerFigure->getOneToMany())
		{
			ddRect r = ownerFigure->getEndFigure()->displayBox();

			view->CalcScrolledPosition(r.x,r.y,&r.x,&r.y);

			int centerX = r.x + r.width/2;
			int centerY = r.y + r.height/2;
		
			context.SetPen(*wxBLACK_PEN);
			context.SetBrush(*wxBLACK_BRUSH);
			

			//DD-TODO: optimize this Hack to get correct size of table connector many triangle
			double XX,YY,factor=0.1,distance;
			bool first=true;
			
			factor = lastFactor;
			do{
				XX= aCopy.x + (bCopy.x - aCopy.x) * factor;
				YY= aCopy.y + (bCopy.y - aCopy.y) * factor;
				distance = sqrt( (aCopy.x - XX)*(aCopy.x - XX) + (aCopy.y - YY)*(aCopy.y - YY));
				if(first && distance > 30)
				{
					factor=0.1;
					first=false;
				}
				lastFactor = factor;	
				if(distance > 20)
					factor=factor*0.75;
				else
					factor=factor*1.20;
			}while(distance > 20 || distance < 10);
		
			wxPoint intersectionLine1(centerX,centerY);
			wxPoint intersectionLine2(X,Y);

		
				//TOP
			if(g.intersection(intersectionLine1,intersectionLine2,r.GetTopLeft(),r.GetTopRight()))
			{
				points[0]=wxPoint(XX,YY);
				points[1]=wxPoint(aCopy.x-7,aCopy.y);
				points[2]=wxPoint(aCopy.x+7,aCopy.y);
				context.DrawPolygon(3,points);

				if(ownerFigure->getIdentifying())
				{
					context.SetPen(wxPen(*wxBLACK,2));
					context.DrawLine(wxPoint(XX-7,YY),wxPoint(XX+7,YY));
					context.SetPen(*wxBLACK_PEN);
				}

			}	//RIGHT
			else if(g.intersection(intersectionLine1,intersectionLine2,r.GetTopRight(),r.GetBottomRight()))
			{
				points[0]=wxPoint(XX,YY);
				points[1]=wxPoint(aCopy.x,aCopy.y-7);
				points[2]=wxPoint(aCopy.x,aCopy.y+7);
				context.DrawPolygon(3,points);
				
				if(ownerFigure->getIdentifying())
				{
					context.SetPen(wxPen(*wxBLACK,2));
					context.DrawLine(wxPoint(XX,YY-7),wxPoint(XX,YY+7));
					context.SetPen(*wxBLACK_PEN);
				}

			}	//BOTTOM
			else if(g.intersection(intersectionLine1,intersectionLine2,r.GetBottomLeft(),r.GetBottomRight()))
			{
				points[0]=wxPoint(XX,YY);
				points[1]=wxPoint(aCopy.x-7,aCopy.y);
				points[2]=wxPoint(aCopy.x+7,aCopy.y);
				context.DrawPolygon(3,points);

				if(ownerFigure->getIdentifying())
				{
					context.SetPen(wxPen(*wxBLACK,2));
					context.DrawLine(wxPoint(XX-7,YY),wxPoint(XX+7,YY));
					context.SetPen(*wxBLACK_PEN);
				}

			}	//LEFT
			else if(g.intersection(intersectionLine1,intersectionLine2,r.GetTopLeft(),r.GetBottomLeft()))
			{
				points[0]=wxPoint(XX,YY);
				points[1]=wxPoint(aCopy.x,aCopy.y-7);
				points[2]=wxPoint(aCopy.x,aCopy.y+7);
				context.DrawPolygon(3,points);

				if(ownerFigure->getIdentifying())
				{
					context.SetPen(wxPen(*wxBLACK,2));
					context.DrawLine(wxPoint(XX,YY-7),wxPoint(XX,YY+7));
					context.SetPen(*wxBLACK_PEN);
				}
			}
			else  //CENTER of star figure or invalid place
			{
				context.DrawText(wxString(wxT("NOOOOOO!!!! porqueeeeeee")),100,100);
			}
			
			return ddPoint(XX,YY);
		}
		return ddPoint(0,0);
	}
	return ddPoint(0,0);
}
