#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# $Id: module.mk 8189 2010-02-25 22:10:21Z dpage $
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/pgscript/exceptions/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/pgscript/exceptions/pgsArithmeticException.h \
	$(srcdir)/include/pgscript/exceptions/pgsAssertException.h \
	$(srcdir)/include/pgscript/exceptions/pgsBreakException.h \
	$(srcdir)/include/pgscript/exceptions/pgsCastException.h \
	$(srcdir)/include/pgscript/exceptions/pgsContinueException.h \
	$(srcdir)/include/pgscript/exceptions/pgsException.h \
	$(srcdir)/include/pgscript/exceptions/pgsInterruptException.h \
	$(srcdir)/include/pgscript/exceptions/pgsParameterException.h

EXTRA_DIST += \
	$(srcdir)/include/pgscript/exceptions/module.mk

