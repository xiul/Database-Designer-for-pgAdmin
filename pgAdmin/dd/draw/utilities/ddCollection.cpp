//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: ddCollection.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddCollection.cpp - Generic implementation of a Collection used by dd.
//
//////////////////////////////////////////////////////////////////////////

// App headers
#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/utilities/ddCollection.h"
#include "dd/draw/main/ddObject.h"

ddCollection::ddCollection(ddCollectionBase *collectionBase)
{
    collection=collectionBase;
}


ddCollection::~ddCollection()
{
    if(collection)
        delete collection;
}


void ddCollection::addItem(ddObject *item)
{
    collection->addItem(item);
}


void ddCollection::removeItem(ddObject *item)
{
    collection->removeItem(item);
}


ddIteratorBase* ddCollection::createIterator()
{
    if(collection)
		return collection->createIterator();
	return NULL;
}

ddIteratorBase* ddCollection::createDownIterator()
{
    if(collection)
		return collection->createDownIterator();
	return NULL;
}


int ddCollection::count()
{
    return collection->count();
}


bool ddCollection::existsObject(ddObject *item)
{
    return collection->existsObject(item);
}


ddObject* ddCollection::getItemAt(int index)
{
    return collection->getItemAt(index);
}

void ddCollection::removeItemAt(int index)
{
	collection->removeItemAt(index);
}

// Remove all items from collection without deleting each one.
void ddCollection::removeAll()
{
    collection->removeAll();
}


void ddCollection::deleteAll()
{
    collection->deleteAll();
}


int ddCollection::getIndex(ddObject *item)
{
    return collection->getIndex(item);
}


void ddCollection::insertAtIndex(ddObject *item, int index)
{
    collection->insertAtIndex(item,index);
}

void ddCollection::replaceAtIndex(ddObject *item, int index){
	collection->replaceAtIndex(item,index);
}