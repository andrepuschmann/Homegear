# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifndef RESCOMP
  ifdef WINDRES
    RESCOMP = $(WINDRES)
  else
    RESCOMP = windres
  endif
endif

ifeq ($(config),debug)
  OBJDIR     = obj/Debug
  TARGETDIR  = bin/Debug
  TARGET     = $(TARGETDIR)/homegear
  DEFINES   += -DFORTIFY_SOURCE=2 -DDEBUG
  INCLUDES  += -IARM\ headers
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -LARM\ libraries -l pthread -l sqlite3 -l readline -l ssl -l crypto
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/Release
  TARGETDIR  = bin/Release
  TARGET     = $(TARGETDIR)/homegear
  DEFINES   += -DFORTIFY_SOURCE=2 -DNDEBUG
  INCLUDES  += -IARM\ headers
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -LARM\ libraries -s -l pthread -l sqlite3 -l readline -l ssl -l crypto
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),profiling)
  OBJDIR     = obj/Profiling
  TARGETDIR  = bin/Profiling
  TARGET     = $(TARGETDIR)/homegear
  DEFINES   += -DFORTIFY_SOURCE=2 -DNDEBUG
  INCLUDES  += -IARM\ headers
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -g -std=c++11 -pg
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -LARM\ libraries -l pthread -l sqlite3 -l readline -l ssl -l crypto -pg
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),debug_rpi)
  CC         = arm-linux-gnueabihf-gcc
  CXX        = arm-linux-gnueabihf-g++
  OBJDIR     = obj/rpi/Debug
  TARGETDIR  = bin/Debug
  TARGET     = $(TARGETDIR)/homegear
  DEFINES   += -DFORTIFY_SOURCE=2 -DDEBUG
  INCLUDES  += -IARM\ headers
  CPPFLAGS  += -MMD -D_GLIBCXX_USE_NANOSLEEP -D_FORTIFY_SOURCE=2 -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -LARM\ libraries -l pthread -l sqlite3 -l readline -l ssl -l crypto
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),release_rpi)
  CC         = arm-linux-gnueabihf-gcc
  CXX        = arm-linux-gnueabihf-g++
  OBJDIR     = obj/rpi/Release
  TARGETDIR  = bin/Release
  TARGET     = $(TARGETDIR)/homegear
  DEFINES   += -DFORTIFY_SOURCE=2 -DNDEBUG
  INCLUDES  += -IARM\ headers
  CPPFLAGS  += -MMD -D_GLIBCXX_USE_NANOSLEEP -D_FORTIFY_SOURCE=2 -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -std=c++11
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -LARM\ libraries -s -l pthread -l sqlite3 -l readline -l ssl -l crypto
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

ifeq ($(config),profiling_rpi)
  CC         = arm-linux-gnueabihf-gcc
  CXX        = arm-linux-gnueabihf-g++
  OBJDIR     = obj/rpi/Profiling
  TARGETDIR  = bin/Profiling
  TARGET     = $(TARGETDIR)/homegear
  DEFINES   += -DFORTIFY_SOURCE=2 -DNDEBUG
  INCLUDES  += -IARM\ headers
  CPPFLAGS  += -MMD -D_GLIBCXX_USE_NANOSLEEP -D_FORTIFY_SOURCE=2 -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -g -std=c++11 -pg
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -LARM\ libraries -l pthread -l sqlite3 -l readline -l ssl -l crypto -pg
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LIBS      += 
  LDDEPS    += 
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(RESOURCES) $(ARCH) $(LIBS) $(LDFLAGS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
  endef
endif

OBJECTS := \
	$(OBJDIR)/BidCoSMessage.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/Peer.o \
	$(OBJDIR)/GD.o \
	$(OBJDIR)/FileDescriptorManager.o \
	$(OBJDIR)/BinaryDecoder.o \
	$(OBJDIR)/BidCoSQueueManager.o \
	$(OBJDIR)/HomeMaticDevices.o \
	$(OBJDIR)/EventHandler.o \
	$(OBJDIR)/HelperFunctions.o \
	$(OBJDIR)/ServiceMessages.o \
	$(OBJDIR)/BidCoSQueue.o \
	$(OBJDIR)/BidCoSPacketManager.o \
	$(OBJDIR)/BidCoSMessages.o \
	$(OBJDIR)/Database.o \
	$(OBJDIR)/User.o \
	$(OBJDIR)/HomeMaticDevice.o \
	$(OBJDIR)/PendingBidCoSQueues.o \
	$(OBJDIR)/BidCoSPacket.o \
	$(OBJDIR)/BinaryEncoder.o \
	$(OBJDIR)/Settings.o \
	$(OBJDIR)/HM-LC-SwX-FM.o \
	$(OBJDIR)/HM-CC-TC.o \
	$(OBJDIR)/HomeMaticCentral.o \
	$(OBJDIR)/HM-SD.o \
	$(OBJDIR)/HM-CC-VD.o \
	$(OBJDIR)/Client.o \
	$(OBJDIR)/Device.o \
	$(OBJDIR)/RPCVariable.o \
	$(OBJDIR)/RPCEncoder.o \
	$(OBJDIR)/RPCHeader.o \
	$(OBJDIR)/HTTP.o \
	$(OBJDIR)/RPCMethods.o \
	$(OBJDIR)/Server.o \
	$(OBJDIR)/SocketOperations.o \
	$(OBJDIR)/RPCDecoder.o \
	$(OBJDIR)/XMLRPCDecoder.o \
	$(OBJDIR)/ClientSettings.o \
	$(OBJDIR)/RPCClient.o \
	$(OBJDIR)/Auth.o \
	$(OBJDIR)/Base64.o \
	$(OBJDIR)/RPCServer.o \
	$(OBJDIR)/XMLRPCEncoder.o \
	$(OBJDIR)/RPCMethod.o \
	$(OBJDIR)/ServerSettings.o \
	$(OBJDIR)/Devices.o \
	$(OBJDIR)/LogicalParameter.o \
	$(OBJDIR)/PhysicalParameter.o \
	$(OBJDIR)/CLIServer.o \
	$(OBJDIR)/CLIClient.o \
	$(OBJDIR)/RFDevice.o \
	$(OBJDIR)/TICC1100.o \
	$(OBJDIR)/Cul.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking homegear
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning homegear
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
ifeq (posix,$(SHELLTYPE))
	-$(SILENT) cp $< $(OBJDIR)
else
	$(SILENT) xcopy /D /Y /Q "$(subst /,\,$<)" "$(subst /,\,$(OBJDIR))" 1>nul
endif
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
endif

$(OBJDIR)/BidCoSMessage.o: BidCoSMessage.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/main.o: main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Peer.o: Peer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/GD.o: GD.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/FileDescriptorManager.o: FileDescriptorManager.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/BinaryDecoder.o: BinaryDecoder.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/BidCoSQueueManager.o: BidCoSQueueManager.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/HomeMaticDevices.o: HomeMaticDevices.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/EventHandler.o: EventHandler.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/HelperFunctions.o: HelperFunctions.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/ServiceMessages.o: ServiceMessages.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/BidCoSQueue.o: BidCoSQueue.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/BidCoSPacketManager.o: BidCoSPacketManager.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/BidCoSMessages.o: BidCoSMessages.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Database.o: Database.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/User.o: User.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/HomeMaticDevice.o: HomeMaticDevice.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/PendingBidCoSQueues.o: PendingBidCoSQueues.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/BidCoSPacket.o: BidCoSPacket.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/BinaryEncoder.o: BinaryEncoder.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Settings.o: Settings.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/HM-LC-SwX-FM.o: Devices/HM-LC-SwX-FM.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/HM-CC-TC.o: Devices/HM-CC-TC.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/HomeMaticCentral.o: Devices/HomeMaticCentral.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/HM-SD.o: Devices/HM-SD.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/HM-CC-VD.o: Devices/HM-CC-VD.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Client.o: RPC/Client.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Device.o: RPC/Device.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RPCVariable.o: RPC/RPCVariable.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RPCEncoder.o: RPC/RPCEncoder.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RPCHeader.o: RPC/RPCHeader.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/HTTP.o: RPC/HTTP.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RPCMethods.o: RPC/RPCMethods.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Server.o: RPC/Server.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/SocketOperations.o: RPC/SocketOperations.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RPCDecoder.o: RPC/RPCDecoder.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/XMLRPCDecoder.o: RPC/XMLRPCDecoder.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/ClientSettings.o: RPC/ClientSettings.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RPCClient.o: RPC/RPCClient.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Auth.o: RPC/Auth.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Base64.o: RPC/Base64.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RPCServer.o: RPC/RPCServer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/XMLRPCEncoder.o: RPC/XMLRPCEncoder.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RPCMethod.o: RPC/RPCMethod.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/ServerSettings.o: RPC/ServerSettings.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Devices.o: RPC/Devices.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/LogicalParameter.o: RPC/LogicalParameter.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/PhysicalParameter.o: RPC/PhysicalParameter.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/CLIServer.o: CLI/CLIServer.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/CLIClient.o: CLI/CLIClient.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/RFDevice.o: RFDevices/RFDevice.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/TICC1100.o: RFDevices/TICC1100.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"
$(OBJDIR)/Cul.o: RFDevices/Cul.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -MF $(@:%.o=%.d) -c "$<"

-include $(OBJECTS:%.o=%.d)
