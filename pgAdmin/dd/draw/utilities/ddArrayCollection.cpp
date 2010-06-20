//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: ddArrayCollection.cpp 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddArrayCollection.cpp - Implementation of Collection Using Arrays
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>

// App headers
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/main/ddObject.h"

// Destructor
ddArrayCollection::~ddArrayCollection()
{
	WX_CLEAR_ARRAY(ddArray);
}


// Add item to array
void ddArrayCollection::addItem(ddObject *item)
{
    ddArray.Add(item);
}


// Remove item from array but don't delete it.
void ddArrayCollection::removeItem(ddObject *item)
{
    ddArray.Remove(item);
}

void ddArrayCollection::removeItemAt(int index)
{
	ddArray.RemoveAt(index);
}


// Create an iterator for the objects inside the array
ddIteratorBase* ddArrayCollection::createIterator()
{
    return (new ddArrayIterator(&ddArray));
}

// Create a Down to iterator for the objects inside the array
ddIteratorBase* ddArrayCollection::createDownIterator()
{
    return (new ddArrayDownIterator(&ddArray));
}

// Return the number of elements inside the array
int ddArrayCollection::count()
{
    return ddArray.Count();
}


// Return true if an element pointer is found inside array
bool ddArrayCollection::existsObject(ddObject *item)
{
    ddObject *found=NULL;
    int size=ddArray.GetCount();
    for(int i=0;i<size;i++)
    {
        if (ddArray.Item(i)==item)
        {
            found=ddArray.Item(i);
            break;
        }
    }
    if(found)
        return true;
    else
        return false;
}


// Delete all elements inside array
void ddArrayCollection::deleteAll()
{
    WX_CLEAR_ARRAY(ddArray);
}


// Removes all elements inside array without deleting
void ddArrayCollection::removeAll()
{
    ddArray.Empty();
}

// Get Item at certain position at Collection 
ddObject* ddArrayCollection::getItemAt(int index)
{
    if(!ddArray.IsEmpty())
        //return ddArray.Item(index);
		return ddArray[index];
    else
        return NULL;
}


int ddArrayCollection::getIndex(ddObject *item)
{
    return ddArray.Index(item);
}


// Insert item into the array before the index
void ddArrayCollection::insertAtIndex(ddObject *item, int index)
{
    ddArray.Insert(item,index);
}

// Replace item into the array at index (if overwrite user should delete manually previous object at index)
void ddArrayCollection::replaceAtIndex(ddObject *item, int index)
{
	ddArray.RemoveAt(index);
	ddArray.Insert(item,index);
}

//
// ddArrayIterator - Manages iterator for the array collection concrete class, from first to last element
//

// Constructor
ddArrayIterator::ddArrayIterator(ddObjsArray *ddPtrsArray)
{
    position=0;
    internalArray=ddPtrsArray;
}


// Get next item in the array for the iterator
ddObject* ddArrayIterator::Next()
{
    ddObject *obj = internalArray->Item(position);
    position++;
    return obj;
}


// Return true if the array has more elements to return
bool ddArrayIterator::HasNext()
{
    int size=internalArray->GetCount();
    if( (size>0) && (position<=(size-1)) )
        return true;
    else
        return false;
}


void ddArrayIterator::ResetIterator()
{
    position=0;
}


//
// ddArrayDownIterator - Manages iterator for the array collection concrete class from last to first element
//

// Constructor
ddArrayDownIterator::ddArrayDownIterator(ddObjsArray *ddPtrsArray)
{
    internalArray=ddPtrsArray;
	position=internalArray->GetCount()-1;
}


// Get next item in the array for the iterator
ddObject* ddArrayDownIterator::Next()
{
    ddObject *obj = internalArray->Item(position);
    position--;
    return obj;
}


// Return true if the array has more elements to return
bool ddArrayDownIterator::HasNext()
{
    int size=internalArray->GetCount();
    if( (size>0) && (position<=(size-1) && position>=0) )
        return true;
    else
        return false;
}


void ddArrayDownIterator::ResetIterator()
{
    position=internalArray->GetCount()-1;
}
