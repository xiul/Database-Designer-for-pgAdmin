//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: ddArrayCollection.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddArrayCollection.h - Implementation of Collection Using Arrays
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDARRAYCOLLECTION_H
#define DDARRAYCOLLECTION_H

// App headers
#include "dd/draw/utilities/ddCollectionBase.h"
#include "dd/draw/main/ddObject.h"


WX_DEFINE_ARRAY_PTR(ddObject *, ddObjsArray);

class ddArrayIterator : public ddIteratorBase
{
public:
    ddArrayIterator(ddObjsArray *ddPtrsArray);
    ddObject* Next();
    bool HasNext();
    void ResetIterator();

private:
    int position;
    ddObjsArray *internalArray;
};

class ddArrayDownIterator : public ddIteratorBase
{
public:
    ddArrayDownIterator(ddObjsArray *ddPtrsArray);
    ddObject* Next();
    bool HasNext();
    void ResetIterator();

private:
    int position;
    ddObjsArray *internalArray;
};

//Create Array Objects used as base for ddCollections
class ddArrayCollection : public ddCollectionBase
{
public:
    ~ddArrayCollection();
    void addItem(ddObject *item);
    void removeItem(ddObject *item);
	virtual void removeItemAt(int index);
    ddIteratorBase* createIterator();
	ddIteratorBase* createDownIterator();
    ddObject* getItemAt(int index);
    int count();
    bool existsObject(ddObject *item);
    int getIndex(ddObject *item);
    void insertAtIndex(ddObject *item, int index);
	void replaceAtIndex(ddObject *item, int index);
    void deleteAll();
    void removeAll();
    ddObject *& operator[](size_t index) { return ddArray[index]; }

private:
    ddObjsArray ddArray;
};
#endif
