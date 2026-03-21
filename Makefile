
all: dwm st dmenu slstatus

dwm:
	$(MAKE) -C dwm clean install

st:
	$(MAKE) -C st clean install

dmenu:
	$(MAKE) -C dmenu clean install

slstatus:
	$(MAKE) -C slstatus clean install

.PHONY: all dwm st dmenu slstatus