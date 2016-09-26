#------------------------------------------------------------
# Makefile
#------------------------------------------------------------
projectRoot = ../../..
include $(projectRoot)/PublishTool/Setting.mk

#------------------------------------------------------------
all: publish
.PHONY: all

manDir = ../../man
publish:
	@$(EchoObject)
	@rm -rf manDir
	@doxygen Doxyfile
	@cp -rv $(manDir) $(LibraryDir)/
	@cp -v Manual.html $(LibraryDir)/man/
.PHONY: publish

#------------------------------------------------------------
# EOF
