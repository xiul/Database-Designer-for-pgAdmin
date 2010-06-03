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
#include "dd/draw/tools/ddAbstractTool.h"


ddAbstractTool::ddAbstractTool(ddDrawingEditor *editor){
	anchorX=0;
	anchorY=0;
	ownerEditor=editor;
}

ddAbstractTool::~ddAbstractTool(){
}

void ddAbstractTool::mouseDown(wxMouseEvent& event){
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
}

void ddAbstractTool::mouseUp(wxMouseEvent& event){
}

void ddAbstractTool::mouseMove(wxMouseEvent& event){
}

void ddAbstractTool::mouseDrag(wxMouseEvent& event){
}

void ddAbstractTool::keyDown(wxKeyEvent& event){
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
}

void ddAbstractTool::keyUp(wxKeyEvent& event)
{
}

void ddAbstractTool::setAnchorCoords(int x, int y){
	anchorX=x;
	anchorY=y;
}

ddDrawingEditor* ddAbstractTool::getDrawingEditor(){
	return ownerEditor;
}

/*
void ddITool::mouseDown(wxMouseEvent& event){
}

void ddITool::mouseUp(wxMouseEvent& event){
}

void ddITool::mouseMove(wxMouseEvent& event){
}

void ddITool::mouseDrag(wxMouseEvent& event){
}

void ddITool::keyDown(wxKeyEvent& event){
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
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

void ddITool::setAnchorCoords(int x, int y){
	anchorX=x;
	anchorY=y;
}*/