## 在 Linux 上编译
作者：康林 (kl222@126.com)

### 环境
#### 操作系统

    ~$ lsb_release -a
    No LSB modules are available.
    Distributor ID:	Ubuntu
    Description:	Ubuntu 20.04.2 LTS
    Release:	20.04
    Codename:	focal

#### QtCreator
版本：v4.15.0。建议使用 v4.15.0 以后版本，以前版本对 cmake 支持不够。

### 工具

- 编译器
  + gcc/g++
  
        ~$ sudo apt install g++ gcc
        
- Qt
  + 系统自带：
  
        ~$ sudo apt install qttools5-dev qttools5-dev-tools qtbase5-dev qtbase5-dev-tools qtmultimedia5-dev qtlocation5-dev libqt5svg5-dev libqtermwidget5-0-dev
        
  + Qt官方发行版本： https://download.qt.io/official_releases/qt/  
    当前使用版本: Qt5.12.11
  + IDE: qtcreator。建议使用 v4.15.0 以后版本，以前版本对 cmake 支持不够。
  
        ~$ sudo apt install sudo apt install qtcreator
  
- git: [http://www.git-scm.com/](http://www.git-scm.com/)

        ~$ sudo apt install git
        
- cmake: [http://www.cmake.org/](http://www.cmake.org/)

        ~$ sudo apt install cmake
        
- automake、autoconf、make

        ~$ sudo apt install automake autoconf make

### 编译

    # 安装依赖库
    ~$ sudo apt install freerdp2-dev libvncserver-dev libssh-dev libtelnet-dev
    ~$ sudo apt install debhelper fakeroot
    # 安装 Qt
    ~$ sudo apt install qttools5-dev qttools5-dev-tools qtbase5-dev qtbase5-dev-tools qtmultimedia5-dev qtlocation5-dev libqt5svg5-dev libqtermwidget5-0-dev
    # 安装 X 开发库
    ~$ sudo apt install libxkbcommon-dev libxkbcommon-x11-dev libx11-xcb-dev libx11-dev libxfixes-dev
    ~$ sudo apt install libutf8proc-dev libpam0g-dev #编译 qtermwidget 需要
    # 编译 TigerVNC
    ~$ sudo apt install libpixman-1-dev
    ~$ git clone https://github.com/KangLin/tigervnc.git
    ~$ cd tigervnc
    ~$ mkdir build
    ~/tigervnc/build$ cmake .. -DCMAKE_INSTALL_PREIX=`pwd`/install
    ~/tigervnc/build$ cmake --build . --target install
    ~/tigervnc/build$ cd ~
    ~$ git clone https://github.com/KangLin/RabbitRemoteControl.git
    ~$ git clone https://github.com/KangLin/RabbitCommon.git
    ~$ cd RabbitRemoteControl
    ~/RabbitRemoteControl$ mkdir build
    ~/RabbitRemoteControl$ cd build
    ~/RabbitRemoteControl/build$ cmake .. -DCMAKE_INSTALL_PREIX=`pwd`/install -Dtigervnc_DIR=~/tigervnc/build/install/lib/cmake
    ~/RabbitRemoteControl/build$ cmake --build . --target install
    

### 依赖库

- [必选] 玉兔公共库: [https://github.com/KangLin/RabbitCommon](https://github.com/KangLin/RabbitCommon)
- [可选] RFB
  + [可选] libvncserver: [https://github.com/LibVNC/libvncserver](https://github.com/LibVNC/libvncserver)
  + [可选] TigerVnc: https://github.com/KangLin/tigervnc
- [可选] FreeRDP: [https://github.com/FreeRDP/FreeRDP](https://github.com/FreeRDP/FreeRDP)
- [可选] [SSH]
  + LIBSSH: [https://www.libssh.org](https://www.libssh.org)
  + LIBSSH2: https://www.libssh2.org/
                 https://github.com/libssh2/libssh2
- [可选] qtermwidget: [https://github.com/lxqt/qtermwidget](https://github.com/lxqt/qtermwidget)
- [可选] libtelnet: [https://github.com/seanmiddleditch/libtelnet](https://github.com/seanmiddleditch/libtelnet)
- [可选] libdatachannel: [https://github.com/paullouisageneau/libdatachannel](https://github.com/paullouisageneau/libdatachannel)

#### 玉兔公共库
此库默认放在与本项目同级目录下，如果没有在同级目录下，则必须指定 CMake 参数:
-DRabbitCommon_DIR=[RabbitCommon 安装目录]

    ~$ git clone https://github.com/KangLin/RabbitCommon.git
    
#### FreeRDP
- 使用系统预编译开发库

      ~$ sudo apt install freerdp2-dev
    
- 使用 vcpkg
  + 源码位置: https://github.com/microsoft/vcpkg/
  + 指定 CMake 参数：-DCMAKE_TOOLCHAIN_FILE=[vcpkg 安装目录]/scripts/buildsystems/vcpkg.cmake
  
        ~$ git clone https://github.com/microsoft/vcpkg.git
        ~$ cd vcpkg
        ~/vcpkg$ ./bootstrap-vcpkg.sh
        ~/vcpkg$ vcpkg install freerdp

- 从源码编译
  + 源码位置：https://github.com/FreeRDP/FreeRDP
  + 编译详见：https://github.com/FreeRDP/FreeRDP/wiki/Compilation
  + 指定 CMake 参数：
    - -DBUILD_FREERDP=ON
    - -DFreeRDP-Client_DIR=[freerdp 安装目录]/lib/cmake/FreeRDP-Client2
    - -DFreeRDP_DIR=[freerdp 安装目录]/lib/cmake/FreeRDP2
    - -DWinPR_DIR=[freerdp 安装目录]/lib/cmake/WinPR2

          ~$ git clone https://github.com/FreeRDP/FreeRDP.git
          ~$ cd FreeRDP
          ~/FreeRDP$ mkdir build
          ~/FreeRDP/build$ cmake .. -DCMAKE_INSTALL_PREIX=`pwd`/install
          ~/FreeRDP/build$ cmake --build . --target install
          
#### libvncserver
- 使用系统预编译开发库

      ~$ sudo apt install libvncserver-dev

- 从源码编译
  + 源码位置：[https://github.com/LibVNC/libvncserver](https://github.com/LibVNC/libvncserver)
  + 指定 CMake 参数：-Dvncclient_DIR=[libvncserver 安装目录]/lib/cmake/LibVncServer

#### TigerVnc
官方只是个应用程序，不支持库。详见：https://github.com/TigerVNC/tigervnc/issues/1123  
所以本人在官方基础上做了修改。源码位置：https://github.com/KangLin/tigervnc  
指定 CMake 参数：-Dtigervnc_DIR=[TigerVNC 安装目录]/lib/cmake

    ~$ sudo apt install libpixman-1-dev
    ~$ git clone https://github.com/KangLin/tigervnc.git
    ~$ cd tigervnc
    ~/tigervnc$ mkdir build
    ~/tigervnc$ cmake .. -DCMAKE_INSTALL_PREIX=`pwd`/install
    ~/tigervnc$ cmake --build . --target install
    
#### libdatachannel
- 使用 vcpkg

      ~/vcpkg$ vcpkg install libdatachannel
      
- 从源码编译
  + 源码位置： [https://github.com/paullouisageneau/libdatachannel](https://github.com/paullouisageneau/libdatachannel)
  + 编译详见： [https://github.com/paullouisageneau/libdatachannel/blob/master/BUILDING.md](https://github.com/paullouisageneau/libdatachannel/blob/master/BUILDING.md)
  + 指定 CMake 参数: -DLibDataChannel_DIR=[libdatachannel 安装目录]/share/cmake/libdatachannel

        ~$ git clone https://github.com/paullouisageneau/libdatachannel.git
        ~$ cd libdatachannel
        ~/libdatachannel$ git submodule update --init --recursive
        ~/libdatachannel$ mkdir build
        ~/libdatachannel$ cd build
        ~/libdatachannel/build$ cmake .. -DCMAKE_INSTALL_PREIX=`pwd`/install
        ~/libdatachannel/build$ cmake --build . --target install

#### qtermwidget
- 使用系统预编译开发库

      ~$ sudo apt install libqtermwidget5-0-dev
      
- 从源码编译
  + 源码位置： [https://github.com/lxqt/qtermwidget](https://github.com/lxqt/qtermwidget)
  + 指定 CMake 参数：-Dqtermwidget5_DIR=[qtermwidget 安装目录]/lib/cmake/qtermwidget5

#### libssh
- 使用系统预编译开发库

      ~$ sudo apt install libssh-dev 

- 使用 vcpkg

      vcpkg install libssh

- 从源码编译
  + 源码位置： [https://www.libssh.org](https://www.libssh.org)
  + 指定 CMake 参数：-Dlibssh_DIR=[libssh 安装目录]/lib/cmake/libssh

### 编译本项目
- 项目位置：[https://github.com/KangLin/RabbitRemoteControl](https://github.com/KangLin/RabbitRemoteControl)
- 下载源码

      ~$ git clone https://github.com/KangLin/RabbitRemoteControl.git

- 设置 CMake 参数
  + RabbitCommon_DIR: RabbitCommon 源码位置
  + BUILD_FREERDP：是否编译 FreeRDP
  + FreeRDP-Client_DIR: [freerdp 安装目录]/lib/cmake/FreeRDP-Client2
  + FreeRDP_DIR: [freerdp 安装目录]/lib/cmake/FreeRDP2
  + WinPR_DIR:PATH: [freerdp 安装目录]/lib/cmake/WinPR2
  + tigervnc_DIR: [TigerVNC 安装目录]/lib/cmake
  + vncclient_DIR: [libvncserver 安装目录]/lib/cmake/LibVncServer
  + LibDataChannel_DIR: [libdatachannel 安装目录]/share/cmake/libdatachannel
  + qtermwidget5_DIR: [qtermwidget 安装目录]/lib/cmake/qtermwidget5
  + libssh_DIR: [libssh 安装目录]/lib/cmake/libssh
  
- 编译
  + 安装目标
    - install-runtime: 只安装运行库和程序
    - install: 安装所有库（运行库与开发库）和程序

  + 命令行编译
  
          ~$ cd RabbitRemoteControl
          ~/RabbitRemoteControl$ mkdir build
          ~/RabbitRemoteControl/build$ cmake .. -DCMAKE_INSTALL_PREIX=`pwd`/install 
          ~/RabbitRemoteControl/build$ cmake --build . --target install-runtime

  + IDE(QtCreator) 编译
    - 打开项目: 菜单->文件->打开文件或项目，选择项目根目录中的 CMakeLists.txt 
    - 配置：点左侧工具栏上的 项目->编译与运行，配置 CMake 参数
    - 编译与运行： 点左侧工具栏上的 “开始调试” 或者按快捷键 F5
