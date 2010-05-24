//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: postgres.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// postgres.h - dummy include
//
//////////////////////////////////////////////////////////////////////////


#include <string.h>

#define lengthof(array) (sizeof (array) / sizeof ((array)[0]))
#define endof(array)	(&array[lengthof(array)])



// to suppress much stuff in parse.h
#define YYTOKENTYPE
#define YYSTYPE int


#define NAMEDATALEN 32
