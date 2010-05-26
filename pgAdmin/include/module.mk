#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# $Id: module.mk 8189 2010-02-25 22:10:21Z dpage $
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/copyright.h \
	$(srcdir)/include/pgAdmin3.h \
	$(srcdir)/include/postgres.h \
	$(srcdir)/include/precomp.h \
	$(srcdir)/include/svnversion.h \
	$(srcdir)/include/version.h

EXTRA_DIST += \
    $(srcdir)/include/module.mk

include $(srcdir)/include/agent/module.mk
include $(srcdir)/include/db/module.mk
include $(srcdir)/include/dlg/module.mk
include $(srcdir)/include/debugger/module.mk
include $(srcdir)/include/ctl/module.mk
include $(srcdir)/include/frm/module.mk
include $(srcdir)/include/images/module.mk
include $(srcdir)/include/parser/module.mk
include $(srcdir)/include/pgscript/module.mk
include $(srcdir)/include/schema/module.mk
include $(srcdir)/include/slony/module.mk
include $(srcdir)/include/gqb/module.mk
include $(srcdir)/include/utils/module.mk

