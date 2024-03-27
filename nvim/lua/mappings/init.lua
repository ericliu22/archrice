vim.g.mapleader = " "


vim.cmd [[
nnoremap <leader>e :NvimTreeFocus<CR>
nnoremap <C-n> :NvimTreeOpen<CR>
nnoremap <C-t> :NvimTreeToggle<CR>
nnoremap <C-f> :NvimTreeFindFile<CR>
map <leader>n :bnext<cr>
map <leader>p :bprevious<cr>
map <leader>x :bdelete<cr>
]]

