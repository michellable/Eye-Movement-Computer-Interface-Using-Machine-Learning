rem This batch script was run in conjunction with testflder.bat. It was used to copy the files shown into each folder which images were being copied from by quadSeg.exe
@echo off
for /d %%i in ("%cd%\*") do ( 
	cd /d "%%i" 
	for /f "delims=" %%i in ('dir /ad/s/b') do (
		cd /d "%%i"
		copy "%cd%\libgcc_s_dw2-1.dll" ".\libgcc_s_dw2-1.dll" && copy "%cd%\libwinpthread-1.dll" ".\libwinpthread-1.dll" && copy "%cd%\libstdc++-6.dll" ".\libstdc++-6.dll" && copy "%cd%\Qt5Core.dll" ".\Qt5Core.dll" && copy "%cd%\quadSeg.exe" ".\quadSeg.exe" 
	)
)