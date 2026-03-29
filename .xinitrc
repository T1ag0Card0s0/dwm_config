~/.screenlayout/dual.sh
export XCURSOR_SIZE=24
xrdb -merge ~/.Xresources
xsetroot -cursor_name left_ptr
xset b off
blueman-applet &
nm-applet &
dunst &
slstatus &
clipmenud &
picom --config ~/.config/picom/picom.conf &
feh --bg-fill ~/Pictures/wallpaper.jpg --bg-fill ~/Pictures/wallpaper.jpg &

exec dwm
