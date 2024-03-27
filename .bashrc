#
# ~/.bashrc
#

#Test
# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
PS1='[\u@\h \W]\$ '

#FUNCTIONS
c () {
	cd $1
	ls -a
}

bprofile() {
	currentdir=$(pwd)
	cd ~
	chezmoi edit --apply .bashrc
	cd $currentdir
	
}

nvimrc() {
	currentdir=$(pwd)
	cd ~/.config/nvim
	chezmoi edit --apply init.lua 
	cd $currentdir
}

hyprconf() {
	currentdir=$(pwd)
	cd ~/.config/hypr
	chezmoi edit --apply hyprland.conf 
	cd $currentdir
}
tmuxconf() {
	currentdir=$(pwd)
	cd ~
	chezmoi edit --apply .tmux.conf 
	cd $currentdir
}

starshipconf() {
	currentdir=$(pwd)
	cd ~/.config
	chezmoi edit --apply starship.toml 
	cd $currentdir
}

resource() {
	source /home/ericliu/.bashrc
}

gf() {
	output=$(fzf)
	if ! [ -z $output ]; then
		directory=$(dirname "$output")
		echo $directory
		c $directory
	fi
}

g() {
	output=$(find * -type d | fzf)
	if ! [ -z $output ]; then
		echo $output
		c $output
	fi
}

#ALIASES
alias py=python3
alias gitrepos="c ~/gitrepos"
alias conf="c ~/.config"
alias scripts="c ~/scripts"
alias resetwaybar="bash resetwaybar.bash"
alias volume="bash volume.bash"
alias sddmconf="c /usr/share/sddm/themes/catppuccin-mocha/"
alias bluetooth="bash bluetooth.bash"
alias ewwconf="c ~/.config/eww"
alias ewwstart="ewwstartup"
alias chome="c ~/Documents/coding"
alias ewwscripts="c ~/.config/eww/scripts"
alias cos="c ~/Documents/os"
alias cait="c ~/Documents/ait"
alias cdma="c ~/Documents/dma"
alias lab3="c ~/Documents/os/labs-24sp-eliu22/lab3"
alias cz="c ~/Documents/zeez"
alias zs="c ~/Documents/zeez/server"
alias za="c ~/Documents/zeez/zeez"
#alias docker="docker -H=tcp://127.0.0.1:4243"
alias cg="c ~/gitrepos"

eval "$(starship init bash)"

. "$HOME/.cargo/env"

bind '"\t":menu-complete'

#STARTUP COMMANDS
pokemon-colorscripts --random 1 --no-title 

#ENVIORNMENT VARIABLES
export EDITOR=nvim
export SUDO_EDITOR=nvim
export BUN_INSTALL="$HOME/.bun"
export PATH=$BUN_INSTALL/bin:$PATH
export PATH=~/scripts:$PATH
export PATH=~/.local/bin:$PATH
export PATH=$PATH:/usr/local/sbin:/usr/local/bin:/usr/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl
export FZF_DEFAULT_OPTS=" \
--color=bg+:#313244,bg:#1e1e2e,spinner:#f5e0dc,hl:#f38ba8 \
--color=fg:#cdd6f4,header:#f38ba8,info:#cba6f7,pointer:#f5e0dc \
--color=marker:#f5e0dc,fg+:#cdd6f4,prompt:#cba6f7,hl+:#f38ba8"
