#------------------------------------------------------------
# 文字コード: UTF-8
#------------------------------------------------------------
projectRoot = .
include $(projectRoot)/PublishTool/Setting.mk

#------------------------------------------------------------
version = 0.07wip
zipFile = crossframework_$(version).zip
#------------------------------------------------------------

all:  publish
.PHONY: all

publish:
	@$(EchoObject)
	@rm -rf $(PublishDirRoot)
	@mkdir -p $(PublishDir)
	@$(MAKE) -C Document
	@$(MAKE) -C Library
	@$(MAKE) -C Tool
	@cd $(PublishDirRoot) && zip $(zipFile) -r ./crossframework
.PHONY: publish
#------------------------------------------------------------
# EOF
