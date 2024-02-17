#!/bin/bash

updateEww() {
		eww update title="$(playerctl -p spotify metadata title)"
		eww update artist="$(playerctl -p spotify metadata artist)"
}

case $1 in
	next)
		playerctl -p spotify next
		updateEww & /home/ericliu/.config/eww/scripts/spotify-image
		;;
	previous)
		playerctl -p spotify previous
		updateEww & /home/ericliu/.config/eww/scripts/spotify-image
		;;
	*)
		notify-send "Somethig fucked up in spotifyctl"
		;;
esac
