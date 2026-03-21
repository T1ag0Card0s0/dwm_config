
all: dwm st dmenu slstatus slock
	mkdir -p ~/.config/dunst
	mkdir -p ~/.config/yazi
	cp dunstrc ~/.config/dunst/
	cp theme.toml ~/.config/yazi
	cp .xinitrc ~/

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

.PHONY: all dwm st dmenu slstatus slock
