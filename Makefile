#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

export TARGET	:=	"libcamera"
export TOPDIR	:=	$(CURDIR)

# specify a directory which contains the nitro filesystem
# this is relative to the Makefile
NITRO_FILES	:=

# These set the information text in the nds file
#GAME_TITLE     := My Wonderful Homebrew
#GAME_SUBTITLE1 := built with devkitARM
#GAME_SUBTITLE2 := http://devitpro.org

include $(DEVKITARM)/ds_rules

.PHONY: checkarm7 checkarm9 clean all

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
all: lib checkarm7 checkarm9

#---------------------------------------------------------------------------------
lib:
	@[ -d $@ ] || mkdir -p $@
	
#---------------------------------------------------------------------------------
checkarm7:
	$(MAKE) -C arm7
	
#---------------------------------------------------------------------------------
checkarm9:
	$(MAKE) -C arm9

#---------------------------------------------------------------------------------

install: all
	@mkdir -p $(DESTDIR)$(DEVKITPRO)/libnds/lib
	@mkdir -p $(DESTDIR)$(DEVKITPRO)/libnds/include
	@cp -v lib/* $(DESTDIR)$(DEVKITPRO)/libnds/lib
	@cp -v include/* $(DESTDIR)$(DEVKITPRO)/libnds/include

uninstall:
	@rm -v $(DESTDIR)$(DEVKITPRO)/libnds/lib/libcamera*
	@rm -v $(DESTDIR)$(DEVKITPRO)/libnds/include/libcamera*

clean:
	@$(MAKE) -C arm9 clean
	@$(MAKE) -C arm7 clean
	@rm -fr $(BUILD) lib
