#!/bin/bash

file_path=$1;
lyne_id=$2;

curl -o ${file_path}/filter_chain https://api.backendless.com/85CB16DE-B11F-D55B-FFDF-11D5902EB700/v1/files/lynes/${lyne_id}/filter_chain
