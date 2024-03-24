#!/bin/bash

updateEww() {
		eww update title="$(playerctl metadata title)"
		eww update artist="$(playerctl metadata artist)"
}

case $1 in
	next)
		playerctl next
		sleep 1
		updateEww
		/home/ericliu/.config/eww/scripts/media-image
		;;
	previous)
		playerctl previous
		sleep 1
		updateEww
		/home/ericliu/.config/eww/scripts/media-image
		;;
	*)
		notify-send "Somethig fucked up in mediactl"
		;;
esac
