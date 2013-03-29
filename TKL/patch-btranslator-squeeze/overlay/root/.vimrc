" Configure Vim Preferences
" Use nocompatible mode to avoid ssh problems with arrow keys
set nocompatible

" Make backspace a bit more flexible
set backspace=indent,eol,start

" If syntax highlighting is available, turn it on
if has("syntax")
  syntax on
endif

" If using vim-full, load additional options
if has("autocmd")

" Have Vim jump to the last position when reopening a file
  au BufReadPost * if line("'\"") > 0 && line("'\"") <= line("$")
    \| exe "normal! g'\"" | endif

" Load indentation rules according to the detected filetype
"	filetype indent on
else	
	set autoindent
	set smartindent
endif

" Set basic options
set background=light
set tabstop=8
set softtabstop=2
set shiftwidth=2
set expandtab
set showcmd
set showmatch
set ignorecase
set smartcase
set ruler
