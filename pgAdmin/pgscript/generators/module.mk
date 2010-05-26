#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# $Id: module.mk 8189 2010-02-25 22:10:21Z dpage $
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/pgscript/generators/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/pgscript/generators/pgsDateGen.cpp \
	$(srcdir)/pgscript/generators/pgsDateTimeGen.cpp \
	$(srcdir)/pgscript/generators/pgsDictionaryGen.cpp \
	$(srcdir)/pgscript/generators/pgsIntegerGen.cpp \
	$(srcdir)/pgscript/generators/pgsNumberGen.cpp \
	$(srcdir)/pgscript/generators/pgsObjectGen.cpp \
	$(srcdir)/pgscript/generators/pgsRealGen.cpp \
	$(srcdir)/pgscript/generators/pgsReferenceGen.cpp \
	$(srcdir)/pgscript/generators/pgsRegexGen.cpp \
	$(srcdir)/pgscript/generators/pgsStringGen.cpp \
	$(srcdir)/pgscript/generators/pgsTimeGen.cpp

EXTRA_DIST += \
	$(srcdir)/pgscript/generators/module.mk

