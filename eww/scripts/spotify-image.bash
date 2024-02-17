#!/bin/bash

url=$(playerctl -p spotify metadata mpris:artUrl)
curl -so ~/eww/.config/spotify-image.jpg $url
echo "scripts/spotify-image.jpg"
