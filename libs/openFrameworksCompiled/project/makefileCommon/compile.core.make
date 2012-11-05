##########################################################################################
# print debug information if needed
ifdef MAKEFILE_DEBUG
    $(info =============================compile.core.make================================)
endif


##########################################################################################
# CORE SPACE SPACE
##########################################################################################

# this is the space delimited list of defines

DEFINES=$(addprefix -D,$(PLATFORM_DEFINES))

# print debug information if needed
ifdef MAKEFILE_DEBUG
    $(info ---DEFINES--- )
    $(foreach v, $(DEFINES),$(info $(v)))
endif

##########################################################################################
# CFLAGS
##########################################################################################

CFLAGS =
# add the defines
CFLAGS += $(DEFINES)
# add the core flags
CFLAGS += -Wall -fexceptions
# add the include cflags
CFLAGS += $(OF_CORE_INCLUDES_CFLAGS)

##########################################################################################
# COMPILER OPTIMIZATIONS and TARGET MAKING
##########################################################################################

ifeq ($(findstring Debug,$(MAKECMDGOALS)),Debug)
    OPTIMIZATION_CFLAGS =$(PLATFORM_OPTIMIZATION_CFLAGS_REQUIRED) $(PLATFORM_OPTIMIZATION_CFLAGS_DEBUG) -g3
    TARGET_NAME = $(MAKECMDGOALS)
    TARGET = $(OF_CORE_LIB_PATH)/libopenFrameworksDebug.a
else ifeq ($(findstring Release,$(MAKECMDGOALS)),Release)
    OPTIMIZATION_CFLAGS =$(PLATFORM_OPTIMIZATION_CFLAGS_REQUIRED) $(PLATFORM_OPTIMIZATION_CFLAGS_RELEASE)
    TARGET_NAME = $(MAKECMDGOALS)
    TARGET = $(OF_CORE_LIB_PATH)/libopenFrameworks.a
else 
    # default to release
    OPTIMIZATION_CFLAGS =$(PLATFORM_OPTIMIZATION_CFLAGS_REQUIRED) $(PLATFORM_OPTIMIZATION_CFLAGS_RELEASE)
    TARGET_NAME = Release
    TARGET = $(OF_CORE_LIB_PATH)/libopenFrameworks.a
endif

ifeq ($(MAKECMDGOALS),clean)
    TARGET =
    TARGET += $(OF_CORE_LIB_PATH)/libopenFrameworks.a
    TARGET += $(OF_CORE_LIB_PATH)/libopenFrameworksDebug.a
endif




CLEANTARGET = $(addprefix Clean,$(TARGET_NAME))

ifdef MAKEFILE_DEBUG
    $(info OPTIMIZATION_CFLAGS=$(OPTIMIZATION_CFLAGS))
    $(info TARGET_NAME=$(TARGET_NAME))
    $(info TARGET=$(TARGET))
    $(info CLEANTARGET=$(CLEANTARGET))
    $(info CFLAGS=$(CFLAGS))
endif



##########################################################################################
# OBJECT FILES
##########################################################################################
OBJFILES = $(patsubst $(OF_ROOT)/%.cpp,%.o,$(OF_CORE_SOURCES))

OBJ_OUTPUT_PATH = obj/$(TARGET_NAME)/
DEPFILES = $(addprefix $(OBJ_OUTPUT_PATH),$(patsubst $(OF_ROOT)/%.cpp,%.d,$(OF_CORE_SOURCES)))
OBJS = $(addprefix $(OBJ_OUTPUT_PATH), $(OBJFILES))

##########################################################################################
##########################################################################################

.PHONY: all Debug Release after clean CleanDebug CleanRelease help

Release: $(TARGET) 

Debug: $(TARGET) 

all: 
	$(MAKE) Debug
	$(MAKE) Release

#This rule does the compilation
$(OBJ_OUTPUT_PATH)%.o: $(OF_ROOT)/%.cpp 
	@echo "compiling object for " $<
	mkdir -p $(@D)
	$(CXX) $(OPTIMIZATION_CFLAGS) $(CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT_PATH)$*.d -MT$(OBJ_OUTPUT_PATH)$*.o -o $@ -c $<

$(TARGET) : $(OBJS) 
	echo "creating " $(TARGET)
	mkdir -p $(@D)
	$(AR) -r "$@" $(OBJS)

-include $(DEPFILES)

#.PHONY: clean CleanDebug CleanRelease
clean:
	rm -Rf obj
	rm -f -v $(TARGET)

$(CLEANTARGET):
	rm -Rf -v $(OBJ_OUTPUT_PATH)
	rm -f -v $(TARGET)

#.PHONY: help
help:
	@echo 
	@echo openFrameworks compiled library makefile
	@echo
	@echo targets:
	@echo "make Debug:		builds the library with debug symbols"
	@echo "make Release:		builds the library with optimizations"
	@echo "make:			= make Release"
	@echo "make all:		= make Debug + make Release"
	@echo "make CleanDebug: cleans the Debug target"
	@echo "make CleanRelease:	cleans the Release target"
	@echo "make clean:		cleans everything"
	@echo

