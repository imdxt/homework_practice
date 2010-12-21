# bash

## ref 
<http://tldp.org/LDP/Bash-Beginners-Guide/html/>

## search

    find . -name "filename"
    grep string filename
    locate filename
    which commandname

often used

    find .|grep filename
    find . -exec grep "$1" '{}' \; -print

    apt-get install ggggg
    sudo !! # run is as root
    ^ggggg^tig^ # then ` sudo apt-get install tig` will be run

now we try __CTRL-r__ then type `gggg`, we can find:

    sudo apt-get install ggggg

## stop a process by force

    ps aux|grep firefox
    kill -9 [the process number of firefox]

## create a tar ball
    
    tar zcvf toy.tgz toy
    tar zxvf toy.tgz 

or we can kill by name

    killall firefox


## gdb

    b 3
    b main.c:3
    b test.c:4
    s
    n

# C
Q: why "hello.c hello.h main.c", why not just put everything in one main.c?

A: check _Program Library HOWTO_

## coding style
`doxygen`

    :dox



## data type

    int i;
    char c;
    float f;

my slides <http://peter-c-pointers.heroku.com/>
## C books

the C Bible: _The C Programming Language_ by K&R

MIT computer introduction course: _think like a computer scientist (python editon)_ 
# history of GNU/Linux
## free software --- GNU
Author: Richard Stallmam
<http://www.gnu.org>
## opensource software ---Linux
Author: Linus 
<http://kernel.org/>

# vim

how to save a file belong to root in vim as common user

    :w !sudo tee %

lots of other good stuff here:
<http://www.catonmat.net/>
## cscope and ctags

`xp`--- to exchange two char

`rc`--- change the char in front of the cursor to 'c'

`zf%`--- to fold a block

`zx` --- to open it

`zc` --- to close it
## quickfix

    :make
    :cwindow
    :cn
    :h quickfix

## my vim slides

<http://vim-showoff-peter.heroku.com/>

## get my vim plugins

    git clone git://github.com/happypeter/peter-vim.git

then follow this:
<http://happypeter.github.com/GitBeijing/vim-conf-share.html>

## insert mode shortcut
__Ctrl-x-l__
__Ctrl-n__
__Ctrl-x-k__

## help

	:h
	:h bd
	:h tutor

## move

`gg` to the top of the file

`G` to the end of the file

`w` to next word

`2w` to next next word

## copy and paste

__SHIFT_V__ then use `j` or `k` to move the cursor

use `y` to copy

and `d` to cut

then move to another place then `p` (paste)

# git

## go back to certain version

     git checkout 2e343ea



	git clone git://....

now how to get the new changes

	cd job-akae.wiki
	git pull	

## git config

for more info:
    
    man git-config

this is my `~/.gitconfig`


    [user]
            name = peter    
            email = username@mydomain.com

    [color]
            diff = auto
            status = auto
            branch = auto
            interactive = auto
            ui = true
            pager = true

    [color "branch"]
            current = yellow reverse
            local = yellow
            remote = green

    [color "diff"]
            meta = yellow bold
            frag = magenta bold
            old = red bold
            new = green bold

    [color "status"]
            added = yellow
            changed = green
            untracked = cyan

    [core]
            editor = vim
                

    [alias]
            co = checkout
            ci = commit -a  
            st = status
            br = branch 

## git create repo

     mkdir gitrepo
     cd gitrepo/
     git init
     vim file.txt
     git add file.txt
     git commit -a -m "first"
     tig
     vim file.txt 
     git commit -a -m "second time"
     tig
     history >git.txt

## github

    rm -rf .ssh/
    ssh-keygen -t dsa
    sudo apt-get install xclip
    cat /home/jiesse/.ssh/id_dsa.pub| xclip -sel clip
    ssh git@github.com
    ssh -v git@github.com


## tig

	apt-get install tig
	man tig
	cd dirname
	tig

## dir

this is my code:

        cd dirname

# How to use markdown

        vim myfile.md
        markdown mymfile.md > myfile.html
        firefox myfile.html&

website: <http://daringfireball.net/projects/markdown/>

# Basics
## firefox

`/` to start search

__Ctrl-G__ find next

__Ctrl-c-l__ change URL

__Ctrl-k__ to google

__Ctrl-r__ refresh

## user and grp

	chmod +x filename 
	chmod -x filename
	chmod 755 filename
	adduser xxx
	su xxx
	ls -l filename

diff and patch
	
	diff -u a b>ab.diff
	rm b
	patch < ab.diff 

check owner of a file

	ls -l filename

delete anything: 

	rm -rf filename

Clear your shell: __Ctrl-l__

show your Desktop: __Alt-Ctrl-d__

Check if the thing is a file or dir

        file dirname
        file filename

create a dir:

        mkdir dirname

# Home Work

## creat your own home page

follow this:
<http://pages.github.com/>
and then you can get sth like this
<http://happypeter.github.com>

## reading

_How to Become a Hacker_ (By Eric S.R)

http://www.beijinglug.org

http://linuxcommand.org/tlcl.php
and you can get it by:

    git clone git://github.com/happypeter/TLCL.git

## listening

Steve Jobs speech at Standford University (you can find it on <www.youku.com>)

Song JinShan : _how to become a good programmer_ 
<http://www.akae.cn/>
