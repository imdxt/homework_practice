#!/bin/bash

markdown /home/peter/job-akae.wiki/note-qhd.md >/home/peter/job-akae.wiki/n.html
firefox /home/peter/job-akae.wiki/n.html &
echo hello

# chmod +x mark.sh
# sudo mv mark.sh /bin
# sudo mv /bin/mark.sh /bin/mmm
# then we can
#
#   $mmm
#
# to run this script
#
# now in vim:
#
#   :%s /\/home\/peter/$HOME/g
#
# '/home/peter' -> '$HOME'
