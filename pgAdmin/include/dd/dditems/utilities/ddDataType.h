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

#ifndef DDDATATYPES_H
#define DDDATATYPES_H

const enum ddDataType {
	dt_bigint = 0,
	dt_boolean,
	dt_bool,
	dt_integer,
	dt_money,
	dt_varchar_n
};

/*
class ddMetaData
{
};
//DD-TODO: add another types and
/*


//readonly string[] ddPgDataTypeString = new string[] =

char const * ddPgDataTypeString[] =
{
	"BIGINT",
	"BOOLEAN",
	"BOOL",
	"INTEGER",
	"MONEY",
	"VARCHAR("
};
*/
/*
You cannot intialize the *contents* of the map at file/static level, only the map-object itself. Somehow you need to have some code, in a function, that adds the values to the map after the map-object is initialized, eg

void A::fill_map() {
  h["A"] = "one";
  h["B"] = "two";
}

Or, to solve the problem of when to initialize the map and it's content:


class A {
    private:
         static const hash_map<char *, char *>& my_map();
    public:
         static char *get_value(char *);
};

const hash_map<char *, char *>& A::my_map() {
   static hash_map<char *, char *> h;
   if(h.empty()){
     h["A"] = "one";
     h["B"] = "two";
   }
   return h;
}

*/

#endif
