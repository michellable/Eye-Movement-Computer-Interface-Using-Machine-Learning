rem This batch script was used in conjunction with testflder.bat to delete files copied into the test subjects folders by copyfolder.bat following running quadSeg.exe
@echo off
for /d %%i in ("%cd%\*") do ( 
	cd /d "%%i" 
	for /f "delims=" %%i in ('dir /ad/s/b') do (
		cd /d "%%i"
		del ".\quadSeg.exe" && del ".\libgcc_s_dw2-1.dll" && del ".\libstdc++-6.dll" && del ".\Qt5Core.dll" && del ".\libwinpthread-1.dll"
	)
)