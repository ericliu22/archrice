local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
  vim.fn.system({
    "git",
    "clone",
    "--filter=blob:none",
    "https://github.com/folke/lazy.nvim.git",
    "--branch=stable", -- latest stable release
    lazypath,
  })
end
vim.opt.rtp:prepend(lazypath)
vim.opt.rtp:prepend(lazypath)
require("lazy").setup({
	"catppuccin/nvim", name = "catppuccin", priority = 1000,
	"norcalli/nvim-colorizer.lua",
	"williamboman/mason.nvim",
	"neovim/nvim-lspconfig",
	"hrsh7th/nvim-cmp",
	"famiu/feline.nvim",
	"hrsh7th/cmp-nvim-lsp",
	"hrsh7th/vim-vsnip",
	"nvim-tree/nvim-tree.lua",
	"nvim-tree/nvim-web-devicons",
	"kkharji/xbase",
	"nvim-lua/plenary.nvim",
	'nvim-telescope/telescope.nvim',
	"epwalsh/obsidian.nvim",
	"nvim-lua/plenary.nvim",
	'nvim-telescope/telescope.nvim',
	'luk400/vim-jukit',
})
