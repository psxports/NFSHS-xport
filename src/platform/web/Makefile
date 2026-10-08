PROJECT_ROOT := $(abspath ../../..)
SHORT_NAME := NFSHS
FULL_NAME := Need for Speed: High Stakes
CONFIG ?= Release
NFSHS_DIAGNOSTICS ?= 0
NFSHS_WEB_RENDER_PROBE ?= 0
STRICT ?= 1
WEB_SOURCE_MAP ?= 1

rwildcard = $(foreach entry,$(wildcard $1*),$(call rwildcard,$(entry)/,$2) $(filter $(subst *,%,$2),$(entry)))

APP_SOURCES := \
	$(wildcard $(PROJECT_ROOT)/src/*.cpp) \
	$(call rwildcard,$(PROJECT_ROOT)/src/game/,*.cpp) \
	$(call rwildcard,$(PROJECT_ROOT)/src/game/,*.c) \
	$(call rwildcard,$(PROJECT_ROOT)/src/frontend/,*.cpp) \
	$(call rwildcard,$(PROJECT_ROOT)/src/frontend/,*.c) \
	$(call rwildcard,$(PROJECT_ROOT)/src/eaclib/,*.cpp) \
	$(call rwildcard,$(PROJECT_ROOT)/src/eaclib/,*.c) \
	$(wildcard $(PROJECT_ROOT)/src/host/*.cpp)
APP_DEFINES := -DAP_WIN=1 -DXPORT_PSX_MEMORY_ONLY=1 -DNFSHS_DIAGNOSTICS=$(NFSHS_DIAGNOSTICS) -D_CRT_SECURE_NO_WARNINGS \
	-DNFSHS_WEB_RENDER_PROBE=$(NFSHS_WEB_RENDER_PROBE) \
	-DWND_TITLE='"Need For Speed: High Stakes (xport)"' -DWND_WIDTH=640 -DWND_HEIGHT=480 -DFIELD_RATE=60

include ../../../../xport/src/platform/web/Makefile

# Reconstructed .c units are C++ translation units, matching the native project
COMMON_FLAGS := $(filter-out -std=c11 -Wno-%,$(COMMON_FLAGS)) -std=c++14 -x c++ -fms-extensions
ifeq ($(STRICT),1)
COMMON_FLAGS += -Werror
LINK_FLAGS += -Wl,--fatal-warnings
endif

ifeq ($(CONFIG),Debug)
ifeq ($(WEB_SOURCE_MAP),0)
BUILD_FLAGS := -O0 -g -D_DEBUG -sASSERTIONS=2
endif
else
# Reconstructed PSX code relies on wrapping arithmetic and overlapping views
BUILD_FLAGS := -O1 -DNDEBUG -fwrapv -fno-strict-aliasing
endif

# Font packet construction still contains optimizer-sensitive recovered code
FONT_OBJECT := $(call object_for,$(PROJECT_ROOT)/src/game/psx/font.cpp)
$(FONT_OBJECT): BUILD_FLAGS := -O0 -DNDEBUG -fwrapv -fno-strict-aliasing

# Header edits must invalidate the linked module
APP_HEADERS := $(call rwildcard,$(PROJECT_ROOT)/src/,*.h) $(wildcard $(XPORT_ROOT)/src/*.h)
$(OUTPUT): $(APP_HEADERS)
