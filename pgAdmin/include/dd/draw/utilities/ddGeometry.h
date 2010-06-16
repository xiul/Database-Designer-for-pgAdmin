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

#ifndef DDGEOMETRY_H
#define DDGEOMETRY_H
#include "dd/draw/main/ddObject.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"

class ddGeometry : public ddObject
{
public:
	static bool lineContainsPoint(double x1, double y1, double x2, double y2, double px, double py);
	static int min(double a, double b);
	static int max(double a, double b);
	static double angleFromPoint(ddRect r, ddPoint point);
	static ddPoint edgePointFromAngle(ddRect r, double angle);
	static double range(double min, double max, double num);
};

#endif
