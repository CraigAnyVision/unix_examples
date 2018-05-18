# QT boilerplate
A simple qt app with qmake and cmake build systems

## Installing tools
```bash
$ wget http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
$ chmod +x qt-unified-linux-x64-online.run        # select latest version, install to /opt/qt/
$ qtchooser -install -local 5.10.1 /opt/qt/5.10.1/gcc_64/bin/qmake 
```
## qmake build
```bash
$ export QT_SELECT=5.10.1
$ qmake                    # creates Makefile
$ make                     # builds target
```

## cmake build
```bash
$ mkdir build && cd build
$ cmake                    # creates Makefile
$ make                     # builds target
```

## Running
```bash
$ export QT_QPA_PLATFORM_PLUGIN_PATH=/opt/qt/5.10.1/gcc_64/plugins
$ ./simpleQt
```
