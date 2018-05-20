**1. Clone wallet sources**

```
git clone https://github.com/jerrimus/QTPenny 
 
 cd QTPenny 
  
 git submodule add -b 3.4 https://github.com/fukuchi/libqrencode libqrencode && git submodule add https://github.com/pennykoin/pennykoin cryptonote
```


**2. build on linux**
Make sure you have qt5base-dev installed 
```
mkdir build && cd build && cmake .. && make
```

**build on windows** 
 
 Install https://download.qt.io/archive/qt/5.8/5.8.0/qt-opensource-windows-x86-msvc2013_64-5.8.0.exe  as well as the pre-reqs from [Pennykoin](https://github.com/jerrimus/pennykoin) 
  
  create a build directory, run :
   
       cmake.exe -DBOOST_ROOT=C:\local\boost_1_67_0 -DBOOST_LIBRARYDIR=C:\local\boost_1_67_0\stage\lib -G "Visual Studio 12 Win64" .. 
        
    in it, then open MAKE ALL project in VS2013 & build as release.
