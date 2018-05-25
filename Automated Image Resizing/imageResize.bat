@echo off
setlocal enableextensions enabledelayedexpansion
for %%a in (*.jpg) do (
set filename=%%a
echo !filename!
call magick convert "!filename!" -resize "252x252^!" "G:\Team Drives\Project Software\test\Quadrant_3_Rescaled\!filename!"
)
pause
endlocal