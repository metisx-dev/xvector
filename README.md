# xvector API
C API for xvector buffer creation and calculation 


Provides cosine similarity on CPU hosts

# Preliminary installs
## Google test
```bash
sudo apt-get install -y libgtest-dev cmake
mkdir -p $HOME/build
cd $HOME/build
sudo cmake /usr/src/googletest/googletest
sudo make
sudo cp lib/libgtest* /usr/lib/
cd ..
sudo rm -rf build
sudo mkdir /usr/local/lib/googletest
sudo ln -s /usr/lib/libgtest.a /usr/local/lib/googletest/libgtest.a
sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/googletest/libgtest_main.a
```


# Build
```bash
cd $PATH_TO_CUR_WORKSPACE
cmake .
make
```

# Output
"xvector/bin/libxvector.so": Shared library for xvector API 


"xvector/bin/xvector_test": executable test sample from xvector/ut


# Usage
## 1. Include header
```c
#include "xvector.h"
```
## 2. Link library to executable
```cmake
# CMakeLists.txt
target_link_libraries(${TargetExecutableName} xvector dl)
```

## 3. Using Google test
### run executable
```bash
cd $PATH_TO_CUR_WORKSPACE\xvector\bin
./xvector_test
```

### VS code extension

Install & run "C++ TestMate"
