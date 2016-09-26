#------------------------------------------------------------
# Makefile
#------------------------------------------------------------
projectRoot = ../..
include $(projectRoot)/PublishTool/Setting.mk
include $(projectRoot)/PublishTool/CopyFiles.mk

#------------------------------------------------------------
# ïœêî
dstDir  = $(LibraryIncludeDir)

#------------------------------------------------------------
all: publish
.PHONY: all

publish:
	@$(EchoObject)
	@$(call copyfiles, ./XG3D, $(dstDir))
	@$(call copyfiles, ./XBase, $(dstDir))
	@$(call copyfiles, ./XData, $(dstDir))
.PHONY: publish

#------------------------------------------------------------
# EOF
