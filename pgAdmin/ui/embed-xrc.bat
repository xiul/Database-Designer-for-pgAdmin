@echo off
REM #######################################################################
REM #
REM # pgAdmin III - PostgreSQL Tools
REM # Copyright (C) 2002 - 2010, The pgAdmin Development Team
REM # This software is released under the PostgreSQL Licence
REM #
REM # embed-xrc.bat - convert xrc files to c++ files
REM #
REM #######################################################################

wxrc -c -o xrcDialogs.cpp *.xrc

