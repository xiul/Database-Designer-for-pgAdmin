#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# $Id: module.mk 8391 2010-05-25 14:46:40Z dpage $
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/utild/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/utils/csvfiles.h \
	$(srcdir)/include/utils/factory.h \
	$(srcdir)/include/utils/favourites.h \
	$(srcdir)/include/utils/md5.h \
	$(srcdir)/include/utils/misc.h \
	$(srcdir)/include/utils/pgfeatures.h \
	$(srcdir)/include/utils/pgDefs.h \
	$(srcdir)/include/utils/pgconfig.h \
	$(srcdir)/include/utils/registry.h \
	$(srcdir)/include/utils/sysLogger.h \
	$(srcdir)/include/utils/sysProcess.h \
	$(srcdir)/include/utils/sysSettings.h \
	$(srcdir)/include/utils/utffile.h \
	$(srcdir)/include/utils/macros.h

EXTRA_DIST += \
        $(srcdir)/include/utils/module.mk

