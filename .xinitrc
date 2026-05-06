#!/bin/sh

[ -f ~/.Xresources ] && xrdb -merge ~/.Xresources

export XCURSOR_SIZE=24
export XDG_CURRENT_DESKTOP=dwm
export XDG_SESSION_DESKTOP=dwm
export XDG_SESSION_TYPE=x11

xsetroot -cursor_name left_ptr
xset b off

~/.screenlayout/office.sh &

dbus-update-activation-environment --systemd DISPLAY XAUTHORITY XDG_CURRENT_DESKTOP XDG_SESSION_DESKTOP XDG_SESSION_TYPE
systemctl --user import-environment DISPLAY XAUTHORITY XDG_CURRENT_DESKTOP XDG_SESSION_DESKTOP XDG_SESSION_TYPE

dex -a -s /etc/xdg/autostart/:~/.config/autostart &

blueman-applet &
nm-applet &
dunst &
slstatus &
clipmenud &
feh --bg-fill ~/Pictures/wallpaper.jpg &
udiskie --tray --automount --notify &

/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

export XDG_CURRENT_DESKTOP=dwm
export XDG_SESSION_DESKTOP=dwm
export XDG_SESSION_TYPE=x11

exec dwm
