#------------------------------------------------------------
# CopyFiles.mk
#------------------------------------------------------------

#------------------------------------------------------------
# �`�F�b�N
ifndef projectRoot
  $(error Not defined variable named 'projectRoot')
endif

#------------------------------------------------------------
# �R�s�[�֐�
defaultFindFilterSrc = \
  "*.bin" \
  "*.c" \
  "*.cpp" \
  "*.h" \
  "*.hpp" \
  "*.m" \
  "*.nib" \
  "*.pbxproj" \
  "*.plist" \
  "*.prop" \
  "*.sln" \
  "*.strings" \
  "*.txt" \
  "*.vcxproj" \
  "*.xcscheme" \

defaultFindFilter := -name "" $(foreach entry,$(defaultFindFilterSrc), -or -type f -name $(entry))

define copyfiles_opt
	@mkdir -p $2
	@find $1 $3 | xargs -P 0 cp --parents -uvt $2
endef

define copyfiles
	$(call copyfiles_opt,$1,$2,$(defaultFindFilter))
endef

#------------------------------------------------------------
# EOF
