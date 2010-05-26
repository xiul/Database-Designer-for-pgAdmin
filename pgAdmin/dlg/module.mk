#######################################################################
#
# pgAdmin III - PostgreSQL Tools
# $Id: module.mk 8189 2010-02-25 22:10:21Z dpage $
# Copyright (C) 2002 - 2010, The pgAdmin Development Team
# This software is released under the PostgreSQL Licence
#
# module.mk - pgadmin/dlg/ Makefile fragment
#
#######################################################################

pgadmin3_SOURCES += \
	$(srcdir)/dlg/dlgAddFavourite.cpp \
	$(srcdir)/dlg/dlgAggregate.cpp \
	$(srcdir)/dlg/dlgCast.cpp \
	$(srcdir)/dlg/dlgClasses.cpp \
	$(srcdir)/dlg/dlgCheck.cpp \
	$(srcdir)/dlg/dlgColumn.cpp \
	$(srcdir)/dlg/dlgConnect.cpp \
	$(srcdir)/dlg/dlgConversion.cpp \
	$(srcdir)/dlg/dlgDatabase.cpp \
	$(srcdir)/dlg/dlgDomain.cpp \
	$(srcdir)/dlg/dlgEditGridOptions.cpp \
	$(srcdir)/dlg/dlgFindReplace.cpp \
	$(srcdir)/dlg/dlgForeignKey.cpp \
	$(srcdir)/dlg/dlgFunction.cpp \
	$(srcdir)/dlg/dlgGroup.cpp \
	$(srcdir)/dlg/dlgHbaConfig.cpp \
	$(srcdir)/dlg/dlgIndex.cpp \
	$(srcdir)/dlg/dlgIndexConstraint.cpp \
	$(srcdir)/dlg/dlgLanguage.cpp \
	$(srcdir)/dlg/dlgMainConfig.cpp \
	$(srcdir)/dlg/dlgManageFavourites.cpp \
	$(srcdir)/dlg/dlgOperator.cpp \
	$(srcdir)/dlg/dlgPackage.cpp \
	$(srcdir)/dlg/dlgPgpassConfig.cpp \
	$(srcdir)/dlg/dlgProperty.cpp \
	$(srcdir)/dlg/dlgReassignDropOwned.cpp \
	$(srcdir)/dlg/dlgRole.cpp \
	$(srcdir)/dlg/dlgRule.cpp \
	$(srcdir)/dlg/dlgSchema.cpp \
	$(srcdir)/dlg/dlgSelectConnection.cpp \
	$(srcdir)/dlg/dlgSequence.cpp \
	$(srcdir)/dlg/dlgServer.cpp \
	$(srcdir)/dlg/dlgSynonym.cpp \
	$(srcdir)/dlg/dlgTable.cpp \
	$(srcdir)/dlg/dlgTablespace.cpp \
	$(srcdir)/dlg/dlgTextSearchConfiguration.cpp \
	$(srcdir)/dlg/dlgTextSearchDictionary.cpp \
	$(srcdir)/dlg/dlgTextSearchParser.cpp \
	$(srcdir)/dlg/dlgTextSearchTemplate.cpp \
	$(srcdir)/dlg/dlgTrigger.cpp \
	$(srcdir)/dlg/dlgType.cpp \
	$(srcdir)/dlg/dlgUser.cpp \
	$(srcdir)/dlg/dlgView.cpp \
	$(srcdir)/dlg/dlgManageMacros.cpp \
	$(srcdir)/dlg/dlgExtTable.cpp \
	$(srcdir)/dlg/dlgSelectDatabase.cpp

EXTRA_DIST += \
        $(srcdir)/dlg/module.mk 

