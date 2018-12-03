#!/bin/bash

file_type=$1;
file_path=$2;
input_file_name=$3;
lyne_id=$4;

if [ "$file_type" = "MP4" ]; then

output_file_name="outputfile.mp4";
avconv -i ${file_path}/${input_file_name} -c:v libx264 -c:a copy ${file_path}/${output_file_name} -y
curl_input_file=$output_file_name;
curl_output_file="cam_feed_0.mp4";

fi

if [ "$file_type" = "FILTER" ]; then

curl_input_file=$input_file_name;
curl_output_file="filter_chain";

fi



curl \
-H application-id:X \
-H secret-key:X \
-H Content-Type:"multipart/form-data" \
-H application-type:REST \
--form upload=@${file_path}/${curl_input_file} \
-X POST \
-v https://api.backendless.com/v1/files/lynes/${lyne_id}/${curl_output_file}?overwrite=true
