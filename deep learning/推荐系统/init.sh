#!/bin/bash
#如果不行,安装pip3
pip install virtualenv -i https://pypi.tuna.tsinghua.edu.cn/simple/
virtualenv -p python py3
source py3/bin/activate
pip3 install jupyter -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install numpy -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install matplotlib -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install pandas -i https://pypi.tuna.tsinghua.edu.cn/simple/
pip3 install sklearn -i https://pypi.tuna.tsinghua.edu.cn/simple/
mkdir algorithm
cd algorithm/
jupyter notebook --allow-root

#允许远程访问https://blog.csdn.net/simple_the_best/article/details/77005400

