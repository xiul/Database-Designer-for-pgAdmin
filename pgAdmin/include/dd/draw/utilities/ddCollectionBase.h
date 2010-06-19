//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: ddCollectionBase.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddCollectionBase.h - A Collection Interface for ERD
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDCOLLECTIONBASE_H
#define DDCOLLECTIONBASE_H

// App headers
#include "dd/draw/main/ddObject.h"

// This class it's like an interface (but with not all advantages of this at runtime)
// If in a future I just don't want to use an array, simple implement this abstract class again
// with the new data structure.

class ddIteratorBase : wxObject
{
public:
    ddIteratorBase() {};
    virtual ddObject* Next() = 0;
    virtual bool HasNext() = 0;
    virtual void ResetIterator() = 0;
};


class ddCollectionBase : wxObject        
{
public:
    ddCollectionBase() {};
    virtual ~ddCollectionBase() {};
    virtual void addItem(ddObject *item) = 0;
    virtual void removeItem(ddObject *item) = 0;
	virtual void removeItemAt(int index) = 0;
    virtual ddObject* getItemAt(int index) = 0;
    virtual ddIteratorBase* createIterator() = 0;
	virtual ddIteratorBase* createDownIterator() = 0;
    virtual int count() = 0;
    virtual bool existsObject(ddObject *item) = 0;
    virtual int getIndex(ddObject *item) = 0;
    virtual void insertAtIndex(ddObject *item, int index) = 0;
	virtual void replaceAtIndex(ddObject *item, int index) = 0;
    virtual void deleteAll()=0;
    virtual void removeAll()=0;           //remove all items from collection without deleting.
};
#endif
