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

class ddGeometry : public ddObject
{
public:
	static bool lineContainsPoint(int x1, int y1, int x2, int y2, int px, int py);
	static int min(int a, int b);
	static int max(int a, int b);
};

#endif
