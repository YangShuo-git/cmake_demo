#！/bin/bash

#########################################################################
# 通过选序号的方式来build，类比lunch
MY_PROJECT=""

help_echo() {
    echo "*********************************************"
    echo "Uage: ./cmake.sh [arg]"
    echo "---------------------------------------------"
    echo "arg:"
    echo "  class"
    echo "  sp"
    echo "  ref"
    echo "  stl"   
    echo "  struct"   
    echo "*********************************************"
    exit
}

exec_function() {
    case $1 in
    "class")
        MY_PROJECT="demo_class"
        echo "exec_function: demo_class"
        ;;
    "sp")
        MY_PROJECT="demo_smartPoint"
        echo "exec_function: demo_smartPoint"
        ;;
    "ref")
        MY_PROJECT="demo_rvalueRef"
        echo "exec_function: demo_rvalueRef"
        ;;
    "stl")
        MY_PROJECT="demo_stl"
        echo "exec_function: demo_stl"
        ;;
    "struct")
        MY_PROJECT="demo_struct"
        echo "exec_function: demo_stl"
        ;;
    *)
        echo -e "\n>> Error param: $1.\n"
        help_echo
        ;;
    esac
}
#########################################################################

# 判断 cmake.sh 接收参数的个数
if [ $# -eq "0" ]; then
    help_echo
elif [ $# -eq "1" ]; then
    exec_function $1
else
    echo -e "\n>> Error params.\n"
    help_echo
fi


echo "--------------build start--------------"
# 判断目录是否存在
if [ -d build ]; then 
    rm -rf build
fi
# 判断文件是否存在
if [ -e struct_file ]; then
    rm struct_file
fi

mkdir build
cd build

# 向cmakelist文件传递参数的方式如下
cmake -D$MY_PROJECT=ON ..

make
echo "--------------build end----------------"