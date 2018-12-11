#!/bin/bash

para_num=$#

#test str

if [ 0 ]
then
    echo "string test..."
    name="aa"
    b=$name".mp4"
    echo $b
    echo ${b: -3}
fi

sub=${b: -4}
if [ $sub == ".jpg" -o $sub == ".mp4" ]
then
    echo "skip this file."
fi

#exit 0

echo $para_num

if [ $para_num -lt 1 ]
then
    echo "input dirpath"
    exit 0
else
    echo "start $0 ..."
fi


if [ false ]
then

echo "start doing ..."
cd $1
filelist=`ls .`
for file in $filelist
do
    #echo $file
    sub=${file: -4}
    if [ $sub == ".jpg" -o $sub == ".mp4" ]
    then
        echo "$file: nothing to do"
        continue
    fi

    #只取日期
    filedate="`ls --full-time $file | cut -d ' ' -f 6`"
    #echo $filedate
    #只取时间
    filetime="`ls --full-time $file | cut -d ' ' -f 7`"
    #echo $filetime
    #echo ${filetime:0:2}${filetime:3:2}${filetime:6:2}
    filesub="_"$filedate"-"${filetime:0:2}${filetime:3:2}${filetime:6:2}
    echo $filesub
    #filepre=$filedate"-"${filetime:0:2}${filetime:3:2}${filetime:6:2}"_"
    #echo $filepre

    filetype="`file $file | cut -d ' ' -f 2`"
    #echo $filetype
    #jpgfile=$filepre$file".jpg"
    #mp4file=$filepre$file".mp4"
    jpgfile=$file$filesub".jpg"
    mp4file=$file$filesub".mp4"
    if [ $filetype == "JPEG" ]
    then
        mv $file $jpgfile
    elif [ $filetype == "ISO" ]
    then
        mv $file $mp4file
    else
        echo $filetype
        echo "$file: unknow filetype, skip"
    fi

    #echo $jpgfile
    #echo $filetype | awk '{if ($2 == "JPEG"){print $jpgfile} else{print $mp4file}}'
    #echo $file

done
fi
