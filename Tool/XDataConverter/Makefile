#------------------------------------------------------------
# Makefile
#------------------------------------------------------------
slnFile   = XDataConverter.sln
outputDir = ./project/bin/Release
binFiles  = \
  $(outputDir)/XDataConverter.exe \
  $(outputDir)/CrossFramework.XDataConverter.dll \
  
dllFiles  = \
  $(outputDir)/CrossFramework.XDataConverter.dll \
  $(outputDir)/CrossFramework.XDataConverter.xml \
  
#------------------------------------------------------------
projectRoot = ../..
include $(projectRoot)/PublishTool/MSBuildRule.mk

#------------------------------------------------------------
# EOF
