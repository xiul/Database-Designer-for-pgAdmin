#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# $Id: module.mk 8189 2010-02-25 22:10:21Z dpage $
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/agent Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/agent/dlgJob.h \
	$(srcdir)/include/agent/dlgSchedule.h  \
	$(srcdir)/include/agent/dlgStep.h  \
	$(srcdir)/include/agent/pgaJob.h  \
	$(srcdir)/include/agent/pgaSchedule.h  \
	$(srcdir)/include/agent/pgaStep.h

EXTRA_DIST += \
        $(srcdir)/include/agent/module.mk

