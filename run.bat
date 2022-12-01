@echo off

set list=A B C D
for %%i in (%list%) DO (
    copy template.cpp template%%i.cpp
)