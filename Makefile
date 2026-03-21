
all: dwm st dmenu slstatus slock

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
