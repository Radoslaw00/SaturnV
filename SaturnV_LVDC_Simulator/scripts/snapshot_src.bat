@echo off
if not exist source_get\src mkdir source_get\src
xcopy src source_get\src /E /I /Y
echo Snapshot of src created in source_get\src
