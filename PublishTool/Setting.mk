#------------------------------------------------------------
# Setting.mk
#------------------------------------------------------------

#------------------------------------------------------------
# projectRoot�`�F�b�N
ifndef projectRoot
  $(error Not defined variable named 'projectRoot')
endif

#------------------------------------------------------------
# �ϐ��ݒ�
EchoObject = echo ---- $@ ----
PublishDirRoot := $(projectRoot)/Publish
PublishDir := $(PublishDirRoot)/crossframework

CommandLineToolDir := $(PublishDir)/CommandLineTool
CLRDLLDir  := $(PublishDir)/CLRDLL
LibraryDir := $(PublishDir)/Library
LibraryBuildDir        := $(LibraryDir)/build
LibraryBuildDemoDir    := $(LibraryBuildDir)/demo
LibraryBuildLibraryDir := $(LibraryBuildDir)/library
LibraryIncludeDir      := $(LibraryDir)/include

MSBuildBin := c:/windows/Microsoft.NET/Framework/v4.0.30319/MSBuild.exe

#------------------------------------------------------------
# EOF
