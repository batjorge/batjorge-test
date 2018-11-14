DATE=`date +%s`

./make_qt_linux.sh $DATE; 
./make_qt_windows.sh $DATE;
./make_daemon_linux_debian.sh $DATE;
