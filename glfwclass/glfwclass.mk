##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=glfwclass
ConfigurationName      :=Debug
WorkspacePath          := "/home/maxis11/projects/wxGameEngine"
ProjectPath            := "/home/maxis11/projects/wxGameEngine/glfwclass"
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
ObjectsFileList        :="glfwclass.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell  pkg-config --libs glfw3) -L/usr/X11R6/lib
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/opt/AMDAPP/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)X11 $(LibrarySwitch)GLEW $(LibrarySwitch)GLU $(LibrarySwitch)GL $(LibrarySwitch)Xext $(LibrarySwitch)OpenCL 
ArLibs                 :=  "X11" "GLEW" "GLU" "GL" "Xext" "OpenCL" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/lib/fglrx 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall -std=c++11 $(shell  pkg-config --cflags glfw3) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(shell  pkg-config --cflags glfw3) $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/engInit$(ObjectSuffix) 



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
$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/maxis11/projects/wxGameEngine/glfwclass/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/engInit$(ObjectSuffix): engInit.cpp $(IntermediateDirectory)/engInit$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/maxis11/projects/wxGameEngine/glfwclass/engInit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/engInit$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/engInit$(DependSuffix): engInit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/engInit$(ObjectSuffix) -MF$(IntermediateDirectory)/engInit$(DependSuffix) -MM "engInit.cpp"

$(IntermediateDirectory)/engInit$(PreprocessSuffix): engInit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/engInit$(PreprocessSuffix) "engInit.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/engInit$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/engInit$(DependSuffix)
	$(RM) $(IntermediateDirectory)/engInit$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) "../.build-debug/glfwclass"


