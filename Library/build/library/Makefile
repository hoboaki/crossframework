#------------------------------------------------------------
# 文字コード: UTF-8
#------------------------------------------------------------
projectRoot = ../../..
include $(projectRoot)/PublishTool/Setting.mk
include $(projectRoot)/PublishTool/CopyFiles.mk

#------------------------------------------------------------
# 変数
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
