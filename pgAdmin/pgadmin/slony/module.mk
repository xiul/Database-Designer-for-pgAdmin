#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# $Id: module.mk 8189 2010-02-25 22:10:21Z dpage $
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/slony/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/slony/dlgRepCluster.cpp \
	$(srcdir)/slony/dlgRepListen.cpp \
	$(srcdir)/slony/dlgRepNode.cpp \
	$(srcdir)/slony/dlgRepPath.cpp \
	$(srcdir)/slony/dlgRepProperty.cpp \
	$(srcdir)/slony/dlgRepSequence.cpp \
	$(srcdir)/slony/dlgRepSet.cpp \
	$(srcdir)/slony/dlgRepSubscription.cpp \
	$(srcdir)/slony/dlgRepTable.cpp \
	$(srcdir)/slony/slCluster.cpp \
	$(srcdir)/slony/slListen.cpp \
	$(srcdir)/slony/slNode.cpp \
	$(srcdir)/slony/slPath.cpp \
	$(srcdir)/slony/slSequence.cpp \
	$(srcdir)/slony/slSet.cpp \
	$(srcdir)/slony/slSubscription.cpp \
	$(srcdir)/slony/slTable.cpp

EXTRA_DIST += \
        $(srcdir)/slony/module.mk


