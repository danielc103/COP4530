#!/bin/tcsh
setenv DIR .
setenv PATH $PATH:usr/ucb:/usr/etc:/usr/local/bin/X11:/usr/bin/X11:/usr/openwi/bin:/usr/ccs/bin:/usr/sbin:.:/usr/local/bin:/usr/bin
echo "Changing directory to $DIR..."
chdir $DIR
echo "Archiving..."
tar -cvf assignment0.tar info.txt
gzip assignment0.tar
uuencode assignment0.tar.gz < assignment0.tar.gz > assignment0
elm -s "assignment0 submission" cop4530p < assignment0
echo "Cleaning up..."
rm -f $DIR/assignment0
rm -f $DIR/assignment0.tar.gz
