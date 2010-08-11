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

	/*ddPoint points[8]; //a,b,leftPoint1,rightPoint1,middlePoint1,leftPoint2,rightPoint2,middlePoint2
	ddGeometry g;
	
	//get parallel lines points
	points[0] = a;
	points[1] = b;

	//calculate terminal points
/*	g.arrowPoints(points[0], points[1], lineDistance, pointDistance, &points[2], &points[3], &points[4]);
	g.arrowPoints(points[0], points[1], lineDistance, pointDistance + 3, &points[5], &points[6], &points[7]);
*/
ddPoint aa=a;
ddPoint bb=b;


/*aa.y+=20;
bb.y+=20;
*/


double X = aa.x + (bb.x - aa.x) * 0.9;
double Y = aa.y + (bb.y - aa.y) * 0.9;






/*int diffX = (bb.x - aa.x);
int diffY = (bb.y - aa.y);

double XX = aa.x + diffX + (diffX<0?8:-8);//(bb.x - aa.x) * 0.1;
double YY = aa.y + diffX + (diffY<0?8:-8);//(bb.y - aa.y) * 0.1;
*/

if(endTerminal){

		if(ownerFigure->getEndFigure())
		{
		ddRect r = ownerFigure->getEndFigure()->displayBox();
		int centerX = r.x + r.width/2;
		int centerY = r.y + r.height/2;
		
		context.SetPen(*wxGREY_PEN);
		context.SetBrush(*wxBLACK_BRUSH);
		
		double XX,YY,factor=0.1,distance;
		do
		{
			XX= aa.x + (bb.x - aa.x) * factor;
			YY= aa.y + (bb.y - aa.y) * factor;
			factor=factor*0.75;
			distance = sqrt( (a.x - XX)*(a.x - XX) + (a.y - YY)*(a.y - YY));
		}while(distance > 30);

		wxPoint angleLine1(centerX,centerY);
		wxPoint angleLine2(X,Y);
//		context.DrawLine(angleLine1,angleLine2);

	/*	ddPoint na = r.GetTopLeft();
		ddPoint nb = r.GetTopRight();
		na.x+=90;
		nb.x+=90;
		context.DrawLine(na,nb);
		*/


		
			//TOP
		if(g.intersection(angleLine1,angleLine2,r.GetTopLeft(),r.GetTopRight()))
		{
			context.DrawText(wxString(wxT("SIIIIII arriba")),100,100);

			points[0]=wxPoint(XX,YY);
			points[1]=wxPoint(aa.x-7,aa.y);
			points[2]=wxPoint(aa.x+7,aa.y);
			context.DrawPolygon(3,points);

			/*context.DrawLine(wxPoint(aa.x-7,aa.y),wxPoint(XX,YY));
			context.DrawLine(wxPoint(aa.x+7,aa.y),wxPoint(XX,YY));
			*/
		}	//RIGHT
		else if(g.intersection(angleLine1,angleLine2,r.GetTopRight(),r.GetBottomRight()))
		{
			context.DrawText(wxString(wxT("SIIIIII derecha")),100,100);

			points[0]=wxPoint(XX,YY);
			points[1]=wxPoint(aa.x,aa.y-7);
			points[2]=wxPoint(aa.x,aa.y+7);
			context.DrawPolygon(3,points);

			/*context.DrawLine(wxPoint(aa.x,aa.y-7),wxPoint(XX,YY));
			context.DrawLine(wxPoint(aa.x,aa.y+7),wxPoint(XX,YY));
			*/
		}	//BOTTOM
		else if(g.intersection(angleLine1,angleLine2,r.GetBottomLeft(),r.GetBottomRight()))
		{
			context.DrawText(wxString(wxT("SIIIIII abajo")),100,100);

			points[0]=wxPoint(XX,YY);
			points[1]=wxPoint(aa.x-7,aa.y);
			points[2]=wxPoint(aa.x+7,aa.y);
			context.DrawPolygon(3,points);

/*			context.DrawLine(wxPoint(aa.x-7,aa.y),wxPoint(XX,YY));
			context.DrawLine(wxPoint(aa.x+7,aa.y),wxPoint(XX,YY));
*/
		}
		else if(g.intersection(angleLine1,angleLine2,r.GetTopLeft(),r.GetBottomLeft()))
		{
			context.DrawText(wxString(wxT("SIIIIII izquierda")),100,100);

			points[0]=wxPoint(XX,YY);
			points[1]=wxPoint(aa.x,aa.y-7);
			points[2]=wxPoint(aa.x,aa.y+7);
			context.DrawPolygon(3,points);
		
/*			context.DrawLine(wxPoint(aa.x,aa.y-7),wxPoint(XX,YY));
			context.DrawLine(wxPoint(aa.x,aa.y+7),wxPoint(XX,YY));
*/
		}
		else
		{
			context.DrawText(wxString(wxT("NOOOOOO!!!! porqueeeeeee")),100,100);
		}

		/*


		
		wxPoint baseLine1(centerX-r.width/2,centerY);
		wxPoint baseLine2(centerX+r.width/2,centerY);
		context.DrawLine(baseLine1,baseLine2);

//Where v1 and v2 are (p1-p2) and (p3-p2).
		ddPoint v1 = baseLine1 - baseLine2;
		ddPoint v2 = angleLine1 - angleLine2;
		double angleX = v1.x*v2.y - v1.y*v2.x;
		double angleY = v1.x*v2.x+v1.y*v2.y;

		double angle = -(180/3.14159)*atan2( angleX, angleY );

		if( (abs(angle)>=150) || (abs(angle)<=30) )
		{
		context.DrawLine(wxPoint(aa.x,aa.y+5),wxPoint(X,Y));
		context.DrawLine(wxPoint(aa.x,aa.y-5),wxPoint(X,Y));
		}

		wxString s; s.Printf(_T("%f"), angle);

		context.DrawText(s,100,100);
		*/
		}

/*		double topX = a.x + (b.x - a.x) * 0.1;
		double topY = a.y + (b.y - a.y) * 0.1;
	
		if(lineIntersection()
		*/
	}
	//	drawBarkerMany(context,points);
	

	//inside points [] are points of terminal

/*	switch (kind) {
			case kindRelationshipTerminal.OneMore:
				if (notation == kindNotation.CrowsFoot)
					DrawCrowFootOneMore (context, points); else
					DrawBarkerMany (context, points);
				break;
			case kindRelationshipTerminal.ZeroMore:
				if (notation == kindNotation.CrowsFoot)
					DrawCrowFootZeroMore (context, points); else
					DrawBarkerMany (context, points);
				break;
			case kindRelationshipTerminal.OneOne:
				if (notation == kindNotation.CrowsFoot)
					DrawCrowFootOneOne (context, points); else
					DrawBarkerOne (context, points);
				break;
			case kindRelationshipTerminal.ZeroOne:
				if (notation == kindNotation.CrowsFoot)
					DrawCrowFootZeroOne (context, points); else
					DrawBarkerOne (context, points);
				break;
			}
*/
/*	ddPoint copyA = ddPoint (a);
	view->CalcScrolledPosition(copyA.x,copyA.y,&copyA.x,&copyA.y);
	ddPoint copyB = ddPoint (b);
	view->CalcScrolledPosition(copyB.x,copyB.y,&copyB.x,&copyB.y);
	context.DrawLine(copyA, copyB);
	
	context.SetPen(wxPen(wxString(wxT("BLACK")),1,wxSOLID));
	//DD-TODO: improve this function is bad just for testing, fix memory leak
	middle = ddPoint(copyA.x+abs(copyA.x - copyB.x),copyA.y+abs(copyA.y - copyB.y));

	//context.DrawCircle(*middle,10);
	context.DrawRectangle(wxRect(copyA.x,copyA.y,5,5));
	context.DrawCircle(copyA,10);
	return middle;
*/
	
	return ddPoint(X,Y);
}

/*
void ddRelationshipTerminal::drawBarkerMany (wxBufferedDC& context, ddPoint points[])
{
	ddPoint anchorsPoints[2];
	calcAnchorPoints(points[0], points[4], anchorsPoints);

	context.SetPen(*wxGREEN);
	context.DrawLine(points[4],anchorsPoints[0]);
	context.SetPen(*wxBLUE);
	context.DrawLine(anchorsPoints[0],anchorsPoints[1]);
	context.SetPen(*wxCYAN);
	context.DrawLine(anchorsPoints[1],points[4]);

/*
			context.LineTo (points[4]);
			context.LineTo (anchors[0]);
			context.LineTo (anchors[1]);
			context.LineTo (points[4]);
			context.FillPreserve ();
			//Identifying
			if (Identifying) {
				context.MoveTo (points[2]);
				context.LineTo (points[3]);
			}


}
*/
/*

void ddRelationshipTerminal::calcAnchorPoints(ddPoint a, ddPoint middle, ddPoint anchors[])
{
	int distanceYtop=0, distanceYbottom=0;

	if(ownerFigure->getEndFigure())
	{
		distanceYtop=ownerFigure->getEndFigure()->displayBox().GetTopLeft().y - middle.y;
		distanceYbottom=ownerFigure->getEndFigure()->displayBox().GetBottomLeft().y - middle.y;
	}

	if ( distanceYtop > 8 || distanceYbottom < -8 ){
		anchors[0].x = a.x + 5;
		anchors[0].y = a.y;
		anchors[1].x = a.x - 5;
		anchors[1].y = a.y;
	}else{
		anchors[0].x = a.x;
		anchors[0].y = a.y + 5;
		anchors[1].x = a.x;
		anchors[1].y = a.y - 5;
	} 

}
/*
bool ddRelationshipTerminal::intersection(ddPoint p1, ddPoint p2, ddPoint p3, ddPoint p4) {
    // Store the values for fast access and easy
    // equations-to-code conversion
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
 
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return NULL;
 
    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    // point of intersection
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
 
	ddGeometry g;
    // Check if the x and y coordinates are within both lines
    if ( x < g.min(x1, x2) || x > g.max(x1, x2) || x < g.min(x3, x4) || x > g.max(x3, x4) )
		return false;
    if ( y < g.min(y1, y2) || y > g.max(y1, y2) || y < g.min(y3, y4) || y > g.max(y3, y4) ) 
		return false;

	return true;
}


/*

bool ddRelationshipTerminal::lineIntersection(ddPoint Line1start, ddPoint Line1end, ddPoint Line2start, ddPoint Line2end)
{
   // Get the slope of the lines
   double slope1 = Line1end.y - Line1start.y / Line1end.x - Line1start.x;
   double slope2 = Line2end.y - Line2start.y / Line2end.x - Line2start.x;
   
   // Get the Y - intercepts of the line
   double yInt1 = slope1 * Line1start.x - Line1start.y;
   double yInt2 = slope2 * Line2start.x - Line2start.y;
   
   // Return false if the lines are paralell
   if (slope1 == slope2)
   {
      return false;
   }
   
   // Calculate the intersection point
   double intersectionX = (yInt2 - yInt1) / (slope1 - slope2);
   double intersectionY = slope1 * intersectionX + yInt1;
   
   // Check if the two line segments intersect
   if (intersectionX < Line1start.x || intersectionY > Line1start.y || intersectionX > Line1end.x || intersectionY < Line1end.y)
   {
      return false;   
   }
   else
   {
      return true;
   }

}
*/

/*

		private void DrawBarkerMany (Context context, PointD[] points)
		{

			PointD[] anchors=calcAnchorPoints(points[0], points[4]);
			context.Stroke ();
			context.LineTo (points[4]);
			context.LineTo (anchors[0]);
			context.LineTo (anchors[1]);
			context.LineTo (points[4]);
			context.FillPreserve ();
			//Identifying
			if (Identifying) {
				context.MoveTo (points[2]);
				context.LineTo (points[3]);
			}
			context.Stroke ();
		}

		private void DrawBarkerOne (Context context, PointD[] points)
		{
			context.MoveTo (points[4]);
			context.LineTo (points[0]);
			//Identifying
			if (Identifying) {
				context.MoveTo (points[2]);
				context.LineTo (points[3]);
			}
			context.Stroke ();

		}
*/