PROGS := dwm st dmenu slstatus slock
USER_HOME ?= ""

ifeq ($(USER_HOME),"")
$(error USER_HOME must not be empty)
endif

all: $(PROGS) install-configs

dwm:
	$(MAKE) -C dwm clean install

st:
	$(MAKE) -C st clean install

dmenu:
	$(MAKE) -C dmenu clean install

slstatus:
	$(MAKE) -C slstatus clean install

slock:
	$(MAKE) -C slock clean install

install-configs:
	mkdir -p $(USER_HOME)/.config/dunst $(USER_HOME)/.config/yazi $(USER_HOME)/.config/picom
	if [ -f $(USER_HOME)/.xinitrc ]; then \
		mv $(USER_HOME)/.xinitrc $(USER_HOME)/.xinitrc.bak_$(date +%Y%m%d_%H%M%S); \
	fi
	cp -fv dunstrc $(USER_HOME)/.config/dunst/
	cp -fv theme.toml $(USER_HOME)/.config/yazi/
	cp -fv .xinitrc $(USER_HOME)/.xinitrc
	cp -fv picom.conf $(USER_HOME)/.config/picom/

clean:
	@echo "Cleaning all programs..."
	$(MAKE) -C dwm clean
	$(MAKE) -C st clean
	$(MAKE) -C dmenu clean
	$(MAKE) -C slstatus clean
	$(MAKE) -C slock clean
	@echo "Clean done."

.PHONY: all $(PROGS) install-configs clean