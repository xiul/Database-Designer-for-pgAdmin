#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# $Id: module.mk 8189 2010-02-25 22:10:21Z dpage $
# Copyright (C) 2002 - 2009, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/debugger/include/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/debugger/ctlCodeWindow.h \
	$(srcdir)/include/debugger/ctlMessageWindow.h \
	$(srcdir)/include/debugger/ctlResultGrid.h \
	$(srcdir)/include/debugger/ctlStackWindow.h \
	$(srcdir)/include/debugger/ctlTabWindow.h \
	$(srcdir)/include/debugger/ctlVarWindow.h \
	$(srcdir)/include/debugger/dbgBreakPoint.h \
	$(srcdir)/include/debugger/dbgConnProp.h \
	$(srcdir)/include/debugger/dbgConst.h \
	$(srcdir)/include/debugger/dbgDbResult.h \
	$(srcdir)/include/debugger/dbgPgConn.h \
	$(srcdir)/include/debugger/dbgPgThread.h \
 	$(srcdir)/include/debugger/dbgResultset.h \
	$(srcdir)/include/debugger/dbgTargetInfo.h \
 	$(srcdir)/include/debugger/debugger.h \
	$(srcdir)/include/debugger/dlgDirectDbg.h \
	$(srcdir)/include/debugger/frmDebugger.h

EXTRA_DIST += \
	$(srcdir)/include/debugger/module.mk


