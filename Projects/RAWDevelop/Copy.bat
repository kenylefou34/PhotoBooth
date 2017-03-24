REM call Copy.bat "$(OutDir)" "$(TargetName)" "$(TargetExt)"
REM La premiere variable d'entree est le chemin complet du dossier contenant la lib (Debug ou Release).
REM La seconde variable d'entree est le nom du projet.
REM La troisieme variable d'entree est l'extension du fichier produit par la compilation.
REM Dans le cas d'une DLL par exemple, la variable contient la chaîne « .dll » (avec le point).
echo ================================= START BAT =================================
echo $(OutDir) : %~1
echo $(TargetName) : %~2
echo $(TargetExt) : %~3
echo $(Configuration) : %~4

REM Variable pour le chemin de destination (attention a ne pas mettre d'espace juste avant et juste après le =
REM Attention bis : bien mettre l'antislash de fin
REM Cette variable peut etre changee en local pour vos tests
set pathDestination=..\BINARIES\
if "%~4"=="x64" (set pathDestination=..\BINARIES_X64\)

REM Copie de la DLL afin d'avoir sur la base un meme vcxproj et d'avoir juste a modifier ce chemin.
echo ..................................
echo .		COPY DLL
echo ..................................
COPY "%~1%~2%~3" "%pathDestination%%~2%~3"

REM De la meme maniere on copie le pdb
echo ..................................
echo .		COPY PDB
echo ..................................
COPY "%~1%~2.pdb" "%pathDestination%%~2.pdb"

REM Cet instruction permet d'encadrer tout ce qui concerne le .bat dans la console
REM MAIS SURTOUT permet de finir le .bat sur une instruction valide ce qui fait que la compilation réussira toujours
REM il faut regarder le détail pour savoir quelles instructions ont échouées.
echo ================================= END BAT =================================
