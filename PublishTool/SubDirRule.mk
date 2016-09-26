#------------------------------------------------------------
# SubDirRule.mk
#------------------------------------------------------------

#------------------------------------------------------------
# チェック
ifndef projectRoot
  $(error Not defined variable named 'projectRoot')
endif
ifndef subDirs
  $(error Not defined variable named 'subDirs')
endif

#------------------------------------------------------------
# インクルード
include $(projectRoot)/PublishTool/Setting.mk

#------------------------------------------------------------
# ルール設定
all: publish
.PHONY: all

publish:
	@$(EchoObject)
	@$(MAKE) $(subDirs)
.PHONY: publish


$(subDirs):
	@$(EchoObject)
	@$(MAKE) -C $@ publish
.PHONY: $(subDirs)

#------------------------------------------------------------
# EOF
