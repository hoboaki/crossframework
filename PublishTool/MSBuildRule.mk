#------------------------------------------------------------
# MSBuildRule.mk
#------------------------------------------------------------

#------------------------------------------------------------
# チェック
ifndef projectRoot
  $(error Not defined variable named 'projectRoot')
endif
ifndef slnFile
  $(error Not defined variable named 'slnFile')
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
	@$(MSBuildBin) $(slnFile) /p:Configuration=Release
	@$(MAKE) copy_files
.PHONY: publish

copy_files: 
	@for f in $(binFiles); do $(MAKE) copy_bin COPY_FILE=$$f; done
	@for f in $(dllFiles); do $(MAKE) copy_dll COPY_FILE=$$f; done
.PHONY: copy_exe

ifdef COPY_FILE
copy_bin:
	@mkdir -pv $(CommandLineToolDir)/bin
	@cp -v $(COPY_FILE) $(CommandLineToolDir)/bin
.PHONY: copy_bin

copy_dll:
	@mkdir -pv $(CLRDLLDir)
	@cp -v $(COPY_FILE) $(CLRDLLDir)/
.PHONY: copy_dll

else
copy_bin:
.PHONY: copy_bin

copy_dll:
.PHONY: copy_dll

endif

#------------------------------------------------------------
# EOF
