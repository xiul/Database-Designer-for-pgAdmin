#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# $Id: module.mk 8189 2010-02-25 22:10:21Z dpage $
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/include/dlg/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/include/dlg/dlgAddFavourite.h \
	$(srcdir)/include/dlg/dlgAggregate.h \
	$(srcdir)/include/dlg/dlgCast.h \
	$(srcdir)/include/dlg/dlgCheck.h \
	$(srcdir)/include/dlg/dlgClasses.h \
	$(srcdir)/include/dlg/dlgColumn.h \
	$(srcdir)/include/dlg/dlgConnect.h \
	$(srcdir)/include/dlg/dlgConversion.h \
	$(srcdir)/include/dlg/dlgDatabase.h \
	$(srcdir)/include/dlg/dlgDomain.h \
	$(srcdir)/include/dlg/dlgEditGridOptions.h \
	$(srcdir)/include/dlg/dlgFindReplace.h \
	$(srcdir)/include/dlg/dlgForeignKey.h \
	$(srcdir)/include/dlg/dlgFunction.h \
	$(srcdir)/include/dlg/dlgGroup.h \
	$(srcdir)/include/dlg/dlgHbaConfig.h \
	$(srcdir)/include/dlg/dlgIndex.h \
	$(srcdir)/include/dlg/dlgIndexConstraint.h \
	$(srcdir)/include/dlg/dlgLanguage.h \
	$(srcdir)/include/dlg/dlgMainConfig.h \
	$(srcdir)/include/dlg/dlgManageFavourites.h \
	$(srcdir)/include/dlg/dlgOperator.h \
	$(srcdir)/include/dlg/dlgPackage.h \
	$(srcdir)/include/dlg/dlgPgpassConfig.h \
	$(srcdir)/include/dlg/dlgProperty.h \
	$(srcdir)/include/dlg/dlgReassignDropOwned.h \
	$(srcdir)/include/dlg/dlgRole.h \
	$(srcdir)/include/dlg/dlgRule.h \
	$(srcdir)/include/dlg/dlgSchema.h \
	$(srcdir)/include/dlg/dlgSelectConnection.h \
	$(srcdir)/include/dlg/dlgSequence.h \
	$(srcdir)/include/dlg/dlgServer.h \
	$(srcdir)/include/dlg/dlgSynonym.h \
	$(srcdir)/include/dlg/dlgTable.h \
	$(srcdir)/include/dlg/dlgTablespace.h \
	$(srcdir)/include/dlg/dlgTextSearchConfiguration.h \
	$(srcdir)/include/dlg/dlgTextSearchDictionary.h \
	$(srcdir)/include/dlg/dlgTextSearchParser.h \
	$(srcdir)/include/dlg/dlgTextSearchTemplate.h \
	$(srcdir)/include/dlg/dlgTrigger.h \
	$(srcdir)/include/dlg/dlgType.h \
	$(srcdir)/include/dlg/dlgUser.h \
	$(srcdir)/include/dlg/dlgView.h \
	$(srcdir)/include/dlg/dlgManageMacros.h \
	$(srcdir)/include/dlg/dlgExtTable.h \
	$(srcdir)/include/dlg/dlgSelectDatabase.h

EXTRA_DIST += \
        $(srcdir)/include/dlg/module.mk

