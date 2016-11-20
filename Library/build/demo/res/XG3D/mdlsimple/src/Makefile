daeConv  = ../../../../../../../Tool/DAEConverter/project/bin/Release/DAEConverter.exe
xg3dConv = ../../../../../../../Tool/XG3DConverter/project/bin/Release/XG3DConverter.exe

all:
	$(MAKE) to_xml
	$(MAKE) to_bin
.PHONY:all

to_xml:
	$(daeConv) ./SkinningSample.dae -xmdl SkinningSample.xmdl
	$(daeConv) ./SimpleShapes.dae -xmdl SimpleShapes.xmdl
	$(daeConv) ./VertexColorSample.dae -xmdl VertexColorSample.xmdl
	#$(daeConv) ./Dragon.dae -xmdl Dragon.xmdl
.PHONY:to_xml

xmdlFiles = $(wildcard *.xmdl)
winFiles = $(foreach f,$(xmdlFiles),../win/res/$(basename $(f)).bin)
macFiles = $(foreach f,$(xmdlFiles),../mac/res/$(basename $(f)).bin)
iosFiles = $(foreach f,$(xmdlFiles),../ios/res/$(basename $(f)).bin)

to_bin: $(winFiles) $(macFiles) $(iosFiles)
.PHONY:to_bin

../win/res/%.bin : %.xmdl
	$(xg3dConv) $@ -platform WIN $<

../mac/res/%.bin : %.xmdl
	$(xg3dConv) $@ -platform MAC $<

../ios/res/%.bin : %.xmdl
	$(xg3dConv) $@ -platform IOS $<
