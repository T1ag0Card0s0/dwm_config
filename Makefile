
all: dwm st dmenu

dwm:
	$(MAKE) -C dwm clean all install

st:
	$(MAKE) -C st clean all install

dmenu:
	$(MAKE) -C dmenu clean all install

.PHONY: all dwm st dmenu