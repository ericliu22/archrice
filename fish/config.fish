if status is-interactive
	# Commands to run in interactive sessions can go here
	alias ls='lsd'
	set PS1 '[\u@\h \W]\$ '
	set fish_greeting
	bind \t complete
	#FUNCTIONS
	function c
		cd $argv
		ls -a
	end

	function bprofile
		set currentdir $(pwd)
		cd ~
		chezmoi edit --apply .bashrc
		cd $currentdir
	end

	function nvimrc
		set currentdir $(pwd)
		cd ~/.config/nvim
		chezmoi edit --apply init.lua 
		cd $currentdir
	end

	function hyprconf
		set currentdir $(pwd)
		cd ~/.config/hypr
		chezmoi edit --apply hyprland.conf 
		cd $currentdir
	end

	function tmuxconf
		set currentdir $(pwd)
		cd ~
		chezmoi edit --apply .tmux.conf 
		cd $currentdir
	end

	function starshipconf
		set currentdir $(pwd)
		cd ~/.config
		chezmoi edit --apply starship.toml 
		cd $currentdir
	end

	function updatemirrors
		curl -s "https://archlinux.org/mirrorlist/?country=US&protocol=https&use_mirror_status=on" | sed -e 's/^#Server/Server/' -e '/^#/d' | rankmirrors -n 10 -
	end

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
	alias cg="c ~/gitrepos"
	alias tiktok="c ~/Documents/tiktok-techjam-2024"
	alias twocents="c ~/Documents/twocents"
	alias lg="lazygit"
	alias manga="c ~/Documents/manga-notifier"

	eval "$(starship init fish)"
	# Set up fzf key bindings
	fzf --fish | source

	#STARTUP COMMANDS

	#ENVIORNMENT VARIABLES
	export EDITOR=nvim
	export SUDO_EDITOR=nvim
	export BUN_INSTALL="$HOME/.bun"
	export PATH=$BUN_INSTALL/bin:$PATH
	export PATH=~/scripts:$PATH
	export PATH=~/.local/bin:$PATH
	export PATH=$PATH:/usr/local/sbin:/usr/local/bin:/usr/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl
	# Set up fzf key bindings and fuzzy completion
	export FZF_DEFAULT_OPTS=" \
	--color=bg+:#313244,bg:#1e1e2e,spinner:#f5e0dc,hl:#f38ba8 \
	--color=fg:#cdd6f4,header:#f38ba8,info:#cba6f7,pointer:#f5e0dc \
	--color=marker:#f5e0dc,fg+:#cdd6f4,prompt:#cba6f7,hl+:#f38ba8"
end
