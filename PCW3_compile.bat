CD /d %~dp0
del /f /q PCW3.Multifix.asi
cd /d src
cl -c /GS- /GF /Ox /EHsc PCW3.Multifix.cpp
link /nodefaultlib /dll /entry:DllMain PCW3.Multifix.obj Kernel32.lib /out:PCW3.Multifix.asi
CD /d %~dp0
cd /d src
del /f /q  "*.obj"