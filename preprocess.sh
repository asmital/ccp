#!/bin/sh
src=$1
target=$2
awk -F\# '$1!="" { print $1 ;} ' $src | awk '{$1=$1;print}' | awk '!/^$/' > $target
