-- disable netrw at the very start of your init.lua
vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1

vim.cmd('set termguicolors')
vim.cmd("set number")


require("lazy-config")
require("nvim-tree").setup()
require("lsp-config")
require("mason").setup()
require("feline-config")
require("mappings")
require("telescope")
require("xbase").setup()

vim.cmd.colorscheme "catppuccin"
