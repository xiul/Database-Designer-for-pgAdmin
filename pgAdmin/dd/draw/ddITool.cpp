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
#include "dd/draw/ddITool.h"


ddITool::ddITool(){
	activatedValue=true;
	undoableValue=false;
}

ddITool::~ddITool(){
}

void ddITool::mouseDown(wxMouseEvent& event){
}

void ddITool::mouseUp(wxMouseEvent& event){
}

void ddITool::mouseMove(wxMouseEvent& event){
}

void ddITool::mouseDrag(wxMouseEvent& event){
}

void ddITool::keyDown(wxKeyEvent& event){
}

void ddITool::keyUp(wxKeyEvent& event)
{
}

void ddITool::activate()
{
	activatedValue=true;
}

void ddITool::deactivate()
{
	activatedValue=false;
}

bool ddITool::activated()
{
	return activatedValue;
}

bool ddITool::undoable(){
	return undoableValue;
}
