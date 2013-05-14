##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=wxGameEngine
ConfigurationName      :=Debug
WorkspacePath          := "/home/maxis11/projects/wxGameEngine"
ProjectPath            := "/home/maxis11/projects/wxGameEngine"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=maxis11
Date                   :=05/14/13
CodeLitePath           :="/home/maxis11/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="wxGameEngine.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell wx-config --debug=yes --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(shell wx-config --cxxflags --unicode=yes --debug=yes) $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/wxMainWindow$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/wxMainWindow$(ObjectSuffix): wxMainWindow.cpp $(IntermediateDirectory)/wxMainWindow$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/maxis11/projects/wxGameEngine/wxMainWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/wxMainWindow$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/wxMainWindow$(DependSuffix): wxMainWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/wxMainWindow$(ObjectSuffix) -MF$(IntermediateDirectory)/wxMainWindow$(DependSuffix) -MM "wxMainWindow.cpp"

$(IntermediateDirectory)/wxMainWindow$(PreprocessSuffix): wxMainWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/wxMainWindow$(PreprocessSuffix) "wxMainWindow.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/wxMainWindow$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/wxMainWindow$(DependSuffix)
	$(RM) $(IntermediateDirectory)/wxMainWindow$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/wxGameEngine"


