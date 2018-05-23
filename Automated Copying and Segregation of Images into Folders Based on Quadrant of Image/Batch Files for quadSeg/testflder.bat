rem This batch script was used in conjunction with quadSeg.exe to run the executable inside the folders of test subjects who took part in the PicMe test
@echo off
for /d %%i in ("%cd%\*") do ( 
	cd /d "%%i" 
	for /f "delims=" %%i in ('dir /ad/s/b') do (
		cd /d "%%i" 
		START /w CMD /c .\quadSeg.exe
	)
)