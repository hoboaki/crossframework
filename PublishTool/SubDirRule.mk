#------------------------------------------------------------
# SubDirRule.mk
#------------------------------------------------------------

#------------------------------------------------------------
# �`�F�b�N
ifndef projectRoot
  $(error Not defined variable named 'projectRoot')
endif
ifndef subDirs
  $(error Not defined variable named 'subDirs')
endif

#------------------------------------------------------------
# �C���N���[�h
include $(projectRoot)/PublishTool/Setting.mk

#------------------------------------------------------------
# ���[���ݒ�
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
