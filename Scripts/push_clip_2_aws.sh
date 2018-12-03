#!/bin/bash

APP_TAG="SL_ENGINE:    "
#LOGS=/home/pi/slc/engine/logs

#How to use this script:
#This scripts allows us to xfr mp4 or coef csv file to S3
#You must always provide the resource csv file path as in input
#You must select between COEF or VID file. COEF means you will transfer COEF csv file. Vid is mp4 clip
#Path to coeff csv file is hardcoded. The coef CSV file name is temporarily "test_0.csv"(See line 13 for details)
#See the Qprocess->start() usage in lyne_engine.cpp as an example

#path to resource csv file: Currently this resides in Desktop/build-Lynes_Manager-Desktop_Qt_5_7_0_GCC_64bit-Debug/$businessId/
csv_path=$1;
#selection between COEF or VID  
file_type=$2; 

#read csv flie
while IFS=, read resourceid value
do
  if [ "$resourceid" = "BUSINESS_ID" ];then
      businessId=$value
      echo $businessId
  fi

  if [ "$resourceid" = "CAMERA_NUMBER" ];then
      camNum=$value
      echo $camNum
  fi
	
  if [ "$resourceid" = "S3KEY" ];then  
      S3KEY=$value
      echo $S3KEY
  fi	

  if [ "$resourceid" = "S3SECRET" ];then
      S3SECRET=$value
      echo $S3SECRET
  fi	
done < $csv_path	
#done < /home/pi/slc/resource_file.csv	

if [ "$file_type" == "VID" ];then

  echo "$APP_TAG Moving filtered MP4 video clip to cloud file server..."
  
  #path=/home/pi/slc/engine/stage0/ 
  path=/home/robert/Desktop/build-Lynes_Manager-Desktop_Qt_5_7_0_GCC_64bit-Debug/$businessId/
  file=out0.mp4
  AWS_PATH=/stage0/
  AWS_MP4_FILE=cam_feed_$camNum.mp4
  bucket=${businessId,,}  
  date=$(date +"%a, %d %b %Y %T %z")
  acl="x-amz-acl:public-read"
  content_type='video/mp4'
  string="PUT\n\n$content_type\n$date\n$acl\n/$bucket$AWS_PATH$AWS_MP4_FILE"
  signature=$(echo -en "${string}" | openssl sha1 -hmac "${S3SECRET}" -binary | base64)
  echo "$APP_TAG Issuing curl command"
  curl -X PUT -T "$path/$file" \
    -H "Host: $bucket.s3.amazonaws.com" \
    -H "Date: $date" \
    -H "Content-Type: $content_type" \
    -H "$acl" \
    -H "Authorization: AWS ${S3KEY}:$signature" \
    https://${bucket}.s3.amazonaws.com${AWS_PATH}${AWS_MP4_FILE}
  echo "$APP_TAG Clip has been uploaded to S3"
else

  echo "$APP_TAG Moving filter chain CSV to cloud"
  #Source params
  path=/home/robert/Desktop/build-Lynes_Manager-Desktop_Qt_5_7_0_GCC_64bit-Debug/$businessId/
  file=test_$camNum.csv

  #Destination params
  AWS_PATH=/stage0/
  AWS_CSV_FILE=test_$camNum.csv
  bucket=${businessId,,}  

  #Curl params
  date=$(date +"%a, %d %b %Y %T %z")
  acl="x-amz-acl:public-read"
  content_type='text/plain'
  string="PUT\n\n$content_type\n$date\n$acl\n/$bucket$AWS_PATH$AWS_CSV_FILE"
  signature=$(echo -en "${string}" | openssl sha1 -hmac "${S3SECRET}" -binary | base64)
  echo "$APP_TAG Issuing curl command"
  curl -X PUT -T "$path/$file" \
    -H "Host: $bucket.s3.amazonaws.com" \
    -H "Date: $date" \
    -H "Content-Type: $content_type" \
    -H "$acl" \
    -H "Authorization: AWS ${S3KEY}:$signature" \
    https://${bucket}.s3.amazonaws.com${AWS_PATH}${AWS_CSV_FILE}

fi












