
vim.cmd [[
let g:jukit_shell_cmd = 'ipython3'
"    - Specifies the command used to start a shell in the output split. Can also be an absolute path. Can also be any other shell command, e.g. `R`, `julia`, etc. (note that output saving is only possible for ipython)
let g:jukit_terminal = ''
"   - Terminal to use. Can be one of '', 'kitty', 'vimterm', 'nvimterm' or 'tmux'. If '' is given then will try to detect terminal (though this might fail, in which case it simply defaults to 'vimterm' or 'nvimterm' - depending on the output of `has("nvim")`)
let g:jukit_auto_output_hist = 0
"   - If set to 1, will create an autocmd with event `CursorHold` to show saved ipython output of current cell in output-history split. Might slow down (n)vim significantly, you can use `set updatetime=<number of milliseconds>` to control the time to wait until CursorHold events are triggered, which might improve performance if set to a higher number (e.g. `set updatetime=1000`).
let g:jukit_use_tcomment = 0
"   - Whether to use tcomment plugin (https://github.com/tomtom/tcomment_vim) to comment out cell markers. If not, then cell markers will simply be prepended with `g:jukit_comment_mark`
let g:jukit_comment_mark = '#'
"   - See description of `g:jukit_use_tcomment` above
let g:jukit_mappings = 1
"   - If set to 0, none of the default function mappings (as specified further down) will be applied
let g:jukit_mappings_ext_enabled = "*"
"   - String or list of strings specifying extensions for which the mappings will be created. For example, `let g:jukit_mappings_ext_enabled=['py', 'ipynb']` will enable the mappings only in `.py` and `.ipynb` files. Use `let g:jukit_mappings_ext_enabled='*'` to enable them for all files.
let g:jukit_notebook_viewer = 'jupyter-notebook'
"   - Command to open .ipynb files, by default jupyter-notebook is used. To use e.g. vs code instead, you could set this to `let g:jukit_notebook_viewer = 'code'`
let g:jukit_convert_overwrite_default = -1
"   - Default setting when converting from .ipynb to .py or vice versa and a file of the same name already exists. Can be of [-1, 0, 1], where -1 means no default (i.e. you'll be prompted to specify what to do), 0 means never overwrite, 1 means always overwrite
let g:jukit_convert_open_default = -1
"   - Default setting for whether the notebook should be opened after converting from .py to .ipynb. Can be of [-1, 0, 1], where -1 means no default (i.e. you'll be prompted to specify what to do), 0 means never open, 1 means always open
let g:jukit_file_encodings = 'utf-8'
"   - Default encoding for reading and writing to files in the python helper functions
let g:jukit_venv_in_output_hist = 1
"   - Whether to also use the provided terminal command for the output history split when starting the splits using the JukitOUtHist command. If 0, the provided terminal command is only used in the output split, not in the output history split.
let g:jukit_highlight_markers = 1
"    - Whether to highlight cell markers or not. You can specify the colors of cell markers by putting e.g. `highlight jukit_cellmarker_colors guifg=#1d615a guibg=#1d615a ctermbg=22 ctermfg=22` with your desired colors in your (neo)vim config. Make sure to define this highlight *after* loading a colorscheme in your (neo)vim config
let g:jukit_enable_textcell_bg_hl = 1
"    - Whether to highlight background of textcells. You can specify the color by putting `highlight jukit_textcell_bg_colors guibg=#131628 ctermbg=0` with your desired colors in your (neo)vim config. Make sure to define this highlight group *after* loading a colorscheme in your (neo)vim config.
let g:jukit_enable_textcell_syntax = 1
"    - Whether to enable markdown syntax highlighting in textcells
let g:jukit_text_syntax_file = $VIMRUNTIME . '/syntax/' . 'markdown.vim'
"    - Syntax file to use for textcells. If you want to define your own syntax matches inside of text cells, make sure to include `containedin=textcell`.
let g:jukit_hl_ext_enabled = '*'
"    - String or list of strings specifying extensions for which the relevant highlighting autocmds regarding marker-highlighting, textcell-highlighting, etc. will be created. For example, `let g:jukit_hl_extensions=['py', 'R']` will enable the defined highlighting options for `.py` and `.R` files. Use `let g:jukit_hl_extensions='*'` to enable them for all files and `let g:jukit_hl_extensions=''` to disable them completely
let g:jukit_output_bg_color = get(g:, 'jukit_output_bg_color', '')
"    - Optional custom background color of output split window (i.e. target window of sent code)
let g:jukit_output_fg_color = get(g:, 'jukit_output_fg_color', '')
"    - Optional custom foreground color of output split window (i.e. target window of sent code)
let g:jukit_outhist_bg_color = get(g:, 'jukit_outhist_bg_color', '#090b1a')
"    - Optional custom background color of output-history window
let g:jukit_outhist_fg_color = get(g:, 'jukit_outhist_fg_color', 'gray')
"    - Optional custom foreground color of output-history window
let g:jukit_output_new_os_window = 0
"    - If set to 1, opens output split in new os-window. Can be used to e.g. write code in one kitty-os-window on your primary monitor while sending code to the shell which is in a seperate kitty-os-window on another monitor.
let g:jukit_outhist_new_os_window = 0
"    - Same as `g:jukit_output_new_os_window`, only for output-history-split

nnoremap <leader>os :call jukit#splits#output()<cr>
"   - Opens a new output window and executes the command specified in `g:jukit_shell_cmd`
nnoremap <leader>ts :call jukit#splits#term()<cr>
"   - Opens a new output window without executing any command
nnoremap <leader>hs :call jukit#splits#history()<cr>
"   - Opens a new output-history window, where saved ipython outputs are displayed
nnoremap <leader>ohs :call jukit#splits#output_and_history()<cr>
"   - Shortcut for opening output terminal and output-history
nnoremap <leader>hd :call jukit#splits#close_history()<cr>
"   - Close output-history window
nnoremap <leader>od :call jukit#splits#close_output_split()<cr>
"   - Close output window
nnoremap <leader>ohd :call jukit#splits#close_output_and_history(1)<cr>
"   - Close both windows. Argument: Whether or not to ask you to confirm before closing.
nnoremap <leader>so :call jukit#splits#show_last_cell_output(1)<cr>
"   - Show output of current cell (determined by current cursor position) in output-history window. Argument: Whether or not to reload outputs if cell id of outputs to display is the same as the last cell id for which outputs were displayed
nnoremap <leader>j :call jukit#splits#out_hist_scroll(1)<cr>
"   - Scroll down in output-history window. Argument: whether to scroll down (1) or up (0)
nnoremap <leader>k :call jukit#splits#out_hist_scroll(0)<cr>
"   - Scroll up in output-history window. Argument: whether to scroll down (1) or up (0)
nnoremap <leader>ah :call jukit#splits#toggle_auto_hist()<cr>
"   - Create/delete autocmd for displaying saved output on CursorHold. Also, see explanation for `g:jukit_auto_output_hist`
nnoremap <leader>sl :call jukit#layouts#set_layout()<cr>
"   - Apply layout (see `g:jukit_layout`) to current splits - NOTE: it is expected that this function is called from the main file buffer/split

nnoremap <leader><space> :call jukit#send#section(0)<cr>
"   - Send code within the current cell to output split (also saves the output if ipython is used and `g:jukit_save_output==1`). Argument: if 1, will move the cursor to the next cell below after sending the code to the split, otherwise cursor position stays the same.
nnoremap <cr> :call jukit#send#line()<cr>
"   - Send current line to output split
vnoremap <cr> :<C-U>call jukit#send#selection()<cr>
"   - Send visually selected code to output split
nnoremap <leader>cc :call jukit#send#until_current_section()<cr>
"   - Execute all cells until the current cell
nnoremap <leader>all :call jukit#send#all()<cr>
"   - Execute all cells

nnoremap <leader>co :call jukit#cells#create_below(0)<cr>
"   - Create new code cell below. Argument: Whether to create code cell (0) or markdown cell (1)
nnoremap <leader>cO :call jukit#cells#create_above(0)<cr>
"   - Create new code cell above. Argument: Whether to create code cell (0) or markdown cell (1)
nnoremap <leader>ct :call jukit#cells#create_below(1)<cr>
"   - Create new textcell below. Argument: Whether to create code cell (0) or markdown cell (1)
nnoremap <leader>cT :call jukit#cells#create_above(1)<cr>
"   - Create new textcell above. Argument: Whether to create code cell (0) or markdown cell (1)
nnoremap <leader>cd :call jukit#cells#delete()<cr>
"   - Delete current cell
nnoremap <leader>cs :call jukit#cells#split()<cr>
"   - Split current cell (saved output will then be assigned to the resulting cell above)
nnoremap <leader>cM :call jukit#cells#merge_above()<cr>
"   - Merge current cell with the cell above
nnoremap <leader>cm :call jukit#cells#merge_below()<cr>
"   - Merge current cell with the cell below
nnoremap <leader>ck :call jukit#cells#move_up()<cr>
"   - Move current cell up
nnoremap <leader>cj :call jukit#cells#move_down()<cr>
"   - Move current cell down
nnoremap <leader>J :call jukit#cells#jump_to_next_cell()<cr>
"   - Jump to the next cell below
nnoremap <leader>K :call jukit#cells#jump_to_previous_cell()<cr>
"   - Jump to the previous cell above
nnoremap <leader>ddo :call jukit#cells#delete_outputs(0)<cr>
"   - Delete saved output of current cell. Argument: Whether to delete all saved outputs (1) or only saved output of current cell (0)
nnoremap <leader>dda :call jukit#cells#delete_outputs(1)<cr>
"   - Delete saved outputs of all cells. Argument: Whether to delete all saved outputs (1) or only saved output of current cell (0)

nnoremap <leader>np :call jukit#convert#notebook_convert("jupyter-notebook")<cr>
"   - Convert from ipynb to py or vice versa. Argument: Optional. If an argument is specified, then its value is used to open the resulting ipynb file after converting script.
nnoremap <leader>ht :call jukit#convert#save_nb_to_file(0,1,'html')<cr>
"   - Convert file to html (including all saved outputs) and open it using the command specified in `g:jukit_html_viewer'. If `g:jukit_html_viewer` is not defined, then will default to `g:jukit_html_viewer='xdg-open'`. Arguments: 1.: Whether to rerun all cells when converting 2.: Whether to open it after converting 3.: filetype to convert to
nnoremap <leader>rht :call jukit#convert#save_nb_to_file(1,1,'html')<cr>
"   - same as above, but will (re-)run all cells when converting to html
nnoremap <leader>pd :call jukit#convert#save_nb_to_file(0,1,'pdf')<cr>
"   - Convert file to pdf (including all saved outputs) and open it using the command specified in `g:jukit_pdf_viewer'. If `g:jukit_pdf_viewer` is not defined, then will default to `g:jukit_pdf_viewer='xdg-open'`. Arguments: 1.: Whether to rerun all cells when converting 2.: Whether to open it after converting 3.: filetype to convert to. NOTE: If the function doesn't work there may be issues with your nbconvert or latex version - to debug, try converting to pdf using `jupyter nbconvert --to pdf --allow-errors --log-level='ERROR' --HTMLExporter.theme=dark </abs/path/to/ipynb> && xdg-open </abs/path/to/pdf>` in your terminal and check the output for possible issues.
nnoremap <leader>rpd :call jukit#convert#save_nb_to_file(1,1,'pdf')<cr>
"   - same as above, but will (re-)run all cells when converting to pdf. NOTE: If the function doesn't work there may be issues with your nbconvert or latex version - to debug, try converting to pdf using `jupyter nbconvert --to pdf --allow-errors --log-level='ERROR' --HTMLExporter.theme=dark </abs/path/to/ipynb> && xdg-open </abs/path/to/pdf>` in your terminal and check the output for possible issues.

]]
