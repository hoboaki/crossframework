tgaConv  = ../../../../../../../Tool/TGAConverter/project/bin/Release/TGAConverter.exe
xg3dConv = ../../../../../../../Tool/XG3DConverter/project/bin/Release/XG3DConverter.exe

all:
	$(MAKE) to_xml
	$(MAKE) to_bin
.PHONY:all

to_xml:
	$(tgaConv) ./RGBA.tga RGBA8.xtex -format RGBA8
	$(tgaConv) ./RGBA.tga RGB8.xtex -format RGB8
	$(tgaConv) ./RGBA.tga RGB5A1.xtex -format RGB5A1
	$(tgaConv) ./RGBA.tga RGBA4.xtex -format RGBA4
	$(tgaConv) ./RGBA.tga RGB565.xtex -format RGB565
.PHONY:to_xml

xtexFiles = $(wildcard *.xtex)
winFiles = $(foreach f,$(xtexFiles),../win/res/$(basename $(f)).bin)
macFiles = $(foreach f,$(xtexFiles),../mac/res/$(basename $(f)).bin)
iosFiles = $(foreach f,$(xtexFiles),../ios/res/$(basename $(f)).bin)

to_bin: $(winFiles) $(macFiles) $(iosFiles)
.PHONY:to_bin

../win/res/%.bin : %.xtex
	$(xg3dConv) $@ -platform WIN $<
	
../mac/res/%.bin : %.xtex
	$(xg3dConv) $@ -platform MAC $<
	
../ios/res/%.bin : %.xtex
	$(xg3dConv) $@ -platform IOS $<
