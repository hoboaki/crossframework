#------------------------------------------------------------
# Makefile
#------------------------------------------------------------
projectRoot = ../../..
include $(projectRoot)/PublishTool/Setting.mk
include $(projectRoot)/PublishTool/CopyFiles.mk

#------------------------------------------------------------
# ïœêî
dstDir  = $(LibraryBuildLibraryDir)

#------------------------------------------------------------
all: publish
.PHONY: all

publish:
	@$(EchoObject)
	@$(call copyfiles, ./ios, $(dstDir))
	@$(call copyfiles, ./macosx, $(dstDir))
	@$(call copyfiles, ./src, $(dstDir))
	@$(call copyfiles_opt, ./windows, $(dstDir),-name "*.vcxproj" -or -name "*.sln" -or -name "*.props")
.PHONY: publish

#------------------------------------------------------------
# EOF
