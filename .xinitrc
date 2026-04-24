#!/bin/sh

[ -f ~/.Xresources ] && xrdb -merge ~/.Xresources
export XCURSOR_SIZE=24
xsetroot -cursor_name left_ptr
xset b off

~/.screenlayout/dual.sh &

dbus-update-activation-environment --systemd DISPLAY XAUTHORITY
dex -a -s /etc/xdg/autostart/:~/.config/autostart &

blueman-applet &
nm-applet &
dunst &
slstatus &
clipmenud &
feh --bg-fill ~/Pictures/wallpaper.jpg &

exec dwm
