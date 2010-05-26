//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: pgfeatures.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// pgfeatures.h PostgreSQL features constants
//
//////////////////////////////////////////////////////////////////////////


#ifndef __FEATURE_H
#define __FEATURE_H

enum
{
    FEATURE_INITIALIZED=0,
    FEATURE_SIZE,
    FEATURE_FILEREAD,
    FEATURE_ROTATELOG,
    FEATURE_POSTMASTER_STARTTIME,
    FEATURE_TERMINATE_BACKEND,
    FEATURE_RELOAD_CONF,
    FEATURE_PGSTATTUPLE,
    FEATURE_PGSTATINDEX,
    FEATURE_FUNCTION_DEFAULTS,
    FEATURE_LAST
};

#endif
