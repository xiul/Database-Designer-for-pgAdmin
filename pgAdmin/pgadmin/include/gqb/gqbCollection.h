//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbCollection.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbCollection.h - Generic implementation of a Collection used by GQB.
//
//////////////////////////////////////////////////////////////////////////

#ifndef GQBCOLLECTION_H
#define GQBCOLLECTION_H

// App headers
#include "gqb/gqbObject.h"
#include "gqb/gqbCollectionBase.h"

class gqbCollection : public wxObject
{
public:
    gqbCollection(gqbCollectionBase *collectionBase);
    virtual ~gqbCollection();
    void addItem(gqbObject *item);
    void removeItem(gqbObject *item);
    void deleteAll();
    void removeAll();
    int count();
    bool existsObject(gqbObject *item);
    int getIndex(gqbObject *item);
    gqbObject* getItemAt(int index);
    void insertAtIndex(gqbObject *item, int index);
    gqbIteratorBase* createIterator();
	gqbIteratorBase* createDownIterator();

private:
    gqbCollectionBase *collection;
};
#endif
