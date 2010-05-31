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
#include "dd/draw/ddDrawingView.h"
#include "dd/draw/ddArrayCollection.h"
#include "dd/draw/ddDrawingEditor.h"

BEGIN_EVENT_TABLE(ddDrawingView, wxScrolledWindow)
EVT_PAINT(ddDrawingView::onPaint)
EVT_MOTION(ddDrawingView::onMotion)
EVT_LEFT_DOWN(ddDrawingView::onMotion)
EVT_RIGHT_DOWN(ddDrawingView::onRightClick)
EVT_LEFT_UP(ddDrawingView::onMotion)
EVT_LEFT_DCLICK(ddDrawingView::onDoubleClick)
EVT_KEY_DOWN(ddDrawingView::OnKeyDown)
END_EVENT_TABLE()


ddDrawingView::ddDrawingView(wxWindow *ddParent, ddDrawingEditor *editor, wxSize size, ddDrawing *initialDrawing)// gqbController *controller, gqbModel *model)
: wxScrolledWindow(ddParent, wxID_ANY, wxPoint(201,0), size,
wxHSCROLL | wxVSCROLL | wxBORDER | wxRETAINED)
{
	drawing=initialDrawing;
	drawingEditor=editor;
	canvasSize=size;
	SetVirtualSizeHints(size);
	selection =  new ddCollection(new ddArrayCollection());
}

ddDrawingView::~ddDrawingView()
{
}

//DD-TODO: set/get an Editor

void ddDrawingView::onPaint(wxPaintEvent& event)
{
    wxPaintDC dcc(this);                          // Prepare Context for Buffered Draw
    wxBufferedDC dc(&dcc, canvasSize);
	//dc.DrawRectangle(wxRect(wxPoint(5,5), wxSize(100,100)));
	ddIFigure *toDraw;
	ddIteratorBase *iterator=drawing->figuresEnumerator();
	while(iterator->HasNext()){
		 toDraw=(ddIFigure *)iterator->Next();
		 toDraw->draw(dc);
	}

}

void ddDrawingView::add(ddIFigure *figure){
	drawing->add(figure);
}


void ddDrawingView::remove(ddIFigure *figure){
	drawing->remove(figure);
}

/* ddCollection* ddDrawingView::insertFigures(ddCollection figures, double dx, double dy, bool check){

}
*/

void ddDrawingView::addToSelection(ddIFigure *figure){
	if(!selection){
		selection = new ddCollection(new ddArrayCollection());
	}
	selection->addItem(figure);	
}

void ddDrawingView::addToSelection(ddCollection *figures){
}

void ddDrawingView::removeFromSelection(ddIFigure *figure){
	if(selection){
		selection->removeItem(figure);		
	}
}

void ddDrawingView::toggleSelection(ddIFigure *figure){
}

void ddDrawingView::clearSelection(){
	selection->removeAll();
}

void ddDrawingView::ScrollToMakeVisible(wxPoint p){
}

void ddDrawingView::ScrollToMakeVisible (ddRect r){
}

ddIHandle* ddDrawingView::findHandle(double x, double y){
	ddIFigure *tmpFigure=NULL;
	ddIHandle *tmpHandle=NULL, *out=NULL;

	//DD-TODO: for each figure in SelectionEnumerator

	ddIteratorBase *selectionIterator=selection->createIterator();
	while(selectionIterator->HasNext()){
		 tmpFigure=(ddIFigure *)selectionIterator->Next();
		 ddIteratorBase *handlesIterator = tmpFigure->handlesEnumerator()->createIterator();
		 while(handlesIterator->HasNext()){
			 tmpHandle= (ddIHandle *)handlesIterator->Next();
			 if(tmpHandle->containsPoint(x,y)){
				 out=tmpHandle;
				 break;
			 }
		 }
	}
	return out;
}

bool ddDrawingView::isFigureSelected(ddIFigure *figure){
	return selection->existsObject(figure);
}

ddIteratorBase* ddDrawingView::selectionFigures(){
	return selection->createIterator();
}

ddDrawing* ddDrawingView::getDrawing(){
	return drawing;
}


void ddDrawingView::onMotion(wxMouseEvent& event)
{
	drawingEditor->tool()->mouseMove(event);
	/*
			if (_drag) {
				// TODO: Move this to a Tool
				ScrollToMakeVisible (point); 
				Editor.Tool.MouseDrag (ev);	
	*/
	

	/*
	static int refresh=1;                         // refresh counter, everytime this values reaches 
	                                              // "refreshRate" value then Refresh while dragging
    // Discover area where event ocurrs
    pos.x=event.GetPosition().x;
    pos.y=event.GetPosition().y;
    this->CalcUnscrolledPosition(pos.x,pos.y,&pos.x,&pos.y);
    gqbObject *anySelected=NULL;

    // Button Down Event is triggered
    if(event.ButtonDown()&& !changeTOpressed)
    {
        this->SetFocus();

        // Which kind of button down was? join creation [click on any column at the 
		// right of checkbox and drag & drop] or table moving [click on title and drag & drop]
        anySelected=controller->getModelSelected(pos,collectionSelected, joinSelected, false);
        if(anySelected)
        {
            // Anything before just forget about it
            changeTOpressed=false;
            joinSource=NULL;
            joinSCol=NULL;
            joinDCol=NULL;
            joinDest=NULL;
            jpos.x=0;
            jpos.y=0;

            if(anySelected->getType()==GQB_QUERYOBJ)
            {
                gqbQueryObject* t = (gqbQueryObject *) (gqbObjectCollection *) anySelected;

                // If click on the title area AND don't click on the columns selection checkbox
                if( (pos.y-t->position.y <= graphBehavior->getTitleRowHeight()))
                    controller->setPointerMode(pt_normal);
                else
                if(pos.x - t->position.x <= 17)
                    controller->setPointerMode(pt_normal);
                else
                    controller->setPointerMode(pt_join);
            }
        }
        else
        {
            anySelected=false;
            mode=pt_normal;
        }

        if(mode==pt_normal)                       // pointer is used to move tables & select/unselect columns
        {
            // getSelected Item [Mark it as selected if possible]
            anySelected=controller->getModelSelected(pos,collectionSelected, joinSelected, true);
            changeTOpressed=true;

            // Do conversion of type object if any found
            if(anySelected)
            {
                if(anySelected->getType()==GQB_QUERYOBJ)
                {
                    collectionSelected = (gqbQueryObject *) (gqbObjectCollection *) anySelected;
                    joinSelected = NULL;
                }
                else if(anySelected->getType()==GQB_JOIN)
                {
                    joinSelected = (gqbQueryJoin *) anySelected;
                    collectionSelected = NULL;
                }
            }
            else
            {
                collectionSelected = NULL;
                joinSelected = NULL;
            }

            if(!collectionSelected)               
            {
				// none selected temp unselect all items
                controller->unsetModelSelected(true);
            }
            else
            {
                gqbColumn *col=graphBehavior->getColumnAtPosition(&pos,collectionSelected);
                if(col)
                {   
					// Add or remove column from model & observers (ex: Grid) (projection part of SQL sentence)
                    controller->processColumnInModel(collectionSelected,col,gridTable);
                }
            }

            if(!joinSelected)
            {
                controller->unsetModelSelected(false);
            }

        }   
		// Pointer is used to add joins
        else if(mode==pt_join)
        {
            anySelected=controller->getModelSelected(pos,collectionSelected, joinSelected, false);

            // Even if I get an object check that it isn't a join
            if( (anySelected) && anySelected->getType()==GQB_QUERYOBJ)
                joinSource = (gqbQueryObject *)(gqbObjectCollection *) anySelected;
            else
                joinSource = NULL;

            if(!joinSource)               
            {
				// creation of join starts
                joinSCol=NULL;
                joinDCol=NULL;
                jpos.x=0;
                jpos.y=0;
            }
            else
            {
                joinSCol=graphBehavior->getColumnAtPosition(&pos,joinSource,joinSource->getWidth());
                jpos=pos;

                // GQB-TODO then draw line between column & pointer
            }
        }

        this->Refresh();
    }

    // Button Up Event is triggered
    if(event.ButtonUp())
    {
		// Pointer is used to move tables & select/unselect columns
		if(mode==pt_normal)
        {
            changeTOpressed=false;
            anySelected=controller->getModelSelected(pos, collectionSelected, joinSelected, false);
            if (anySelected && anySelected->getType() == GQB_JOIN)
            {
                gqbJoinsPanel *jPanel = wxDynamicCast( joinsPanel, gqbJoinsPanel );
                jPanel->selectJoin((gqbQueryJoin *)anySelected);
            }
        }                                         
        // Pointer is used to add joins
		else if(mode==pt_join)
        {
            anySelected=controller->getModelSelected(pos,collectionSelected, joinSelected, false);

            // Even if I get an object check that it isn't a join
            if( (anySelected) && anySelected->getType()==GQB_QUERYOBJ)
            {
                joinDest = (gqbQueryObject *)(gqbObjectCollection *) anySelected;
                // Validate not self joins [in this version tables can be duplicated to create same effect]
                if(joinDest==joinSource)
                {
                    joinDest=NULL;
                }
            }else
            joinDest = NULL;

			// Creation of join starts
            if(!joinDest)                         
            {
                joinSource=NULL;
                joinSCol=NULL;
                joinDCol=NULL;
                joinDest=NULL;
                jpos.x=0;
                jpos.y=0;
            }
            else
            {
                joinDCol=graphBehavior->getColumnAtPosition(&pos,joinDest,joinDest->getWidth());
                if(joinDCol)
                {
                    // GQB-TODO: Allow other type of joins
                    gqbQueryJoin *qj=controller->addJoin(joinSource,joinSCol,joinDest,joinDCol,_equally);
                    graphBehavior->calcAnchorPoint(qj);
                    this->joinsGridTable->AppendJoin(qj);
                }
                // Let the temporary join line to be draw again [Don't destroy anything because all object where own by other objects this are just pointers]
                joinSource=NULL;
                joinSCol=NULL;
                joinDest=NULL;
                joinDCol=NULL;
                jpos.x=0;
                jpos.y=0;
            }
        }

        controller->setPointerMode(pt_normal);    //when button is up, pointer mode should be only normal
        this->Refresh();
    }

    // Mouse is Dragged while mouse button is down
    if (event.Dragging()&&pressed)
    {
        if(mode==pt_normal)
        {
            if(collectionSelected)
            {
                // GQB-TODO: same as gqbGraphBehavior.h [find a way to not hard code the 17 default value]
                if((pos.x > collectionSelected->position.x+17) || (pos.x < collectionSelected->position.x) )
                {
                    graphBehavior->UpdatePosObject(collectionSelected,pos.x,pos.y,40);
                }

                // Don't draw too much when dragging table around canvas [lower cpu use]
				if(refresh%refreshRate==0)
                {
                    this->Refresh();
                    refresh=1;
                }
                else
                    refresh++;

            }
        }
        else if(mode==pt_join)
        {
            if(joinSource && !joinDest)
            {
                this->Refresh();
            }

        }
    }*/
}


void ddDrawingView::OnKeyDown(wxKeyEvent& event)
{
/*    if(event.GetKeyCode() == WXK_DELETE)
    {
        if(collectionSelected)
        {
            this->joinsGridTable->removeJoins(collectionSelected);
            controller->removeTableFromModel(collectionSelected,gridTable,orderByLGridTable,orderByRGridTable);
            collectionSelected=NULL;
            this->Refresh();
        }

        if(joinSelected)
        {
            this->joinsGridTable->removeJoin(joinSelected);
            controller->removeJoin(joinSelected);
            joinSelected=NULL;
            this->Refresh();
        }
    }*/
}



void ddDrawingView::onRightClick(wxMouseEvent& event)
{
    /*
	// GQB-TODO: Validate Alias
    gqbObject *anySelected=NULL;
    wxPoint pdc=event.GetPosition();
    pdc.x=event.GetPosition().x;
    pdc.y=event.GetPosition().y;
    this->CalcUnscrolledPosition(pdc.x,pdc.y,&pdc.x,&pdc.y);
    anySelected=controller->getModelSelected(pdc,cTempSelected, jTempSelected, false);
    if(anySelected)
    {
        if(anySelected->getType()==GQB_QUERYOBJ)
        {
            if(!m_rightTables)
            {
                m_rightTables = new wxMenu;
                m_rightTables->Append(GQB_RMT_SETALIAS, _("&Set Alias for table"));
                m_rightTables->Append(GQB_RMT_DELETE, _("&Delete Table"));
                m_rightTables->AppendSeparator();
                m_rightTables->Append(GQB_REFRESH, _("&Refresh"));

            }
            cTempSelected=(gqbQueryObject *) (gqbObjectCollection *) anySelected;
            jTempSelected=NULL;
            PopupMenu(m_rightTables, event.GetPosition());
        }

        if(anySelected->getType()==GQB_JOIN)
        {
            if(!m_rightJoins)
            {
                m_rightJoins = new wxMenu;
                m_rightJoins->Append(GQB_RMJ_DELETE, _("&Delete Join"));
                m_rightJoins->AppendSeparator();
                m_rightJoins->Append(GQB_REFRESH, _("&Refresh"));
            }
            cTempSelected=NULL;
            jTempSelected=(gqbQueryJoin *) anySelected;;
            PopupMenu(m_rightJoins, event.GetPosition());
        }
    }
    else
    {
        if(!m_gqbPopup)
        {
            m_gqbPopup = new wxMenu;
            m_gqbPopup->Append(GQB_REFRESH, _("&Refresh"));
        }
        PopupMenu(m_gqbPopup, event.GetPosition());
    }
	*/
}

void ddDrawingView::onDoubleClick(wxMouseEvent& event)
{
	/*
    // GQB-TODO: Validate Alias
    gqbObject *anySelected=NULL;
    wxPoint pdc=event.GetPosition();
    pdc.x=event.GetPosition().x;
    pdc.y=event.GetPosition().y;
    this->CalcUnscrolledPosition(pdc.x,pdc.y,&pdc.x,&pdc.y);

    anySelected=controller->getModelSelected(pdc,cTempSelected, jTempSelected, false);
    if(anySelected)
    {
        if(anySelected->getType()==GQB_QUERYOBJ)
        {
            gqbQueryObject *t = (gqbQueryObject *) (gqbObjectCollection *) anySelected;

            // Because a bug that scrolled automatically the panel of the view if this dialog is called, then assign
            // as his parent the main container of the view, and void the bug
            wxTextEntryDialog dialog(controller->getDialogParent(),
			wxString::Format(_("Enter an alias for table %s"), t->getName().c_str()),
            _("Please enter an alias for the table."),
                wxT(""),
                wxOK | wxCANCEL| wxCENTRE);
            dialog.SetValue(t->getAlias());
            if (dialog.ShowModal() == wxID_OK)
            {
                t->setAlias(dialog.GetValue());
                joinsPanel->Refresh();

                // hack to avoid misplaced joins anchors after insert an alias that trigger a table graph resize (bigger)
                this->Refresh();
                this->Update(); //force refresh
                graphBehavior->UpdatePosObject(t,t->position.x,t->position.y,0);
            }
        }
        else if(anySelected->getType()==GQB_JOIN)
        {
            gqbQueryJoin *j = (gqbQueryJoin *) anySelected;

            controller->getTabs()->ChangeSelection(ti_joinsPanel);
            gqbJoinsPanel *jPanel = wxDynamicCast( joinsPanel, gqbJoinsPanel );
            jPanel->selectJoin(j);
        }
    }
    this->Refresh();
	*/
}





/*


wxPoint ddDrawingView::drawingToView(double x, double y){
}

wxPoint ddDrawingView::viewToDrawing(double x, double y){
}

ddIDrawing* ddDrawingView::drawing(){
}

ddIDrawing* ddDrawingView::editor(){   //DD-TODO: debe retornar un editor
}



int ddDrawingView::selectionCount(){
}
ddRect ddDrawingView::visibleArea(){
}
*/