#!/bin/bash

 # Class A Public IPv4 adresses
 # Range 1.0.0.0 - 127.255.255.255
 
 function rand_ip(){
 
 local first=$(seq 1 127 | shuf -n 1)
 local second=$(seq 0 255 | shuf -n 1)
 local third=$(seq 0 255 | shuf -n 1)
 local fourth=$(seq 0 255 | shuf -n 1)
 
 local ip="$first.$second.$third.$fourth"
 echo $ip
}
 
 
 # All possible code answers
 # 2xx - Success
 # 200 - OK. Standard response for successful HTTP requests.
 # 201 - Created. The request has been fulfilled, resulting in the creation of a new resource.
 # 4xx - Client errors
 # 400 - Bad request.
 # 401 - Unauthorized. Authentication is required and has failed or has not yet been provided.
 # 403 - Forbidden. The request contained valid data and was understood by the server, but the server is refusing action.
 # 404 - Not found. The requested resource could not be found but may be available in the future.
 # 5xx - Server errors
 # 500 - Internal server error. A generic error message, given when an unexpected condition was encountered and no more specific message is suitable.
 # 501 - Not Implemented. The server either does not recognize the request method, or it lacks the ability to fulfil the request.
 # 502 - Bad gateway. The server was acting as a gateway or proxy and received an invalid response from the upstream server.
 # 503 - Service Unavaliable. The server cannot handle the request (because it is overloaded or down for maintenance).
 
 function rand_code_answer(){
 
 local list_of_possible_code_answers="200 201 400 401 403 404 500 501 502 503"
 
 local i=$((1 + $RANDOM % 10))
 
 local code_answer=$(echo $list_of_possible_code_answers | awk -v awkvar="$i" '{print $awkvar; }')
 echo $code_answer
 
}
 
 # GET - Retrieving resources.
 # POST - Creating new resources or other types of content submission.
 # PUT - Updating resources. Note: some types of resources cannot be updated.
 # PATCH - Unlike PUT Request, PATCH does partial update e.g. Fields that need to be updated by the client, only that field is updated without modifying the other field.
 # DELETE - Deleting resources. A successful delete will return a 200 or 204 response, even if no payload is attached.
 
 function rand_method(){
 
 local list_of_possible_methods="GET POST PUT PATCH DELETE"
 
 local i=$((1 + $RANDOM % 5))
 
 local method=$(echo $list_of_possible_methods | awk -v awkvar="$i" '{print $awkvar; }')
 echo $method
 
}
 
 function rand_date(){
 
 local rand_year=$((1900 + $RANDOM % 123))
 
 local list_of_months="Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec"
 local i_month=$((1 + $RANDOM % 12))
 local list_of_days="31 28 31 30 31 30 31 31 30 31 30 31"
 local list_of_days_leap="31 29 31 30 31 30 31 31 30 31 30 31"
 
 local month=$(echo $list_of_months | awk -v awkvar="$i_month" '{ print $awkvar; }')
 
 local temp4=$((rand_year%4))
 local temp100=$((rand_year%100))
 local temp400=$((rand_year%400))
 local leap=0
 
 if [[ $temp4 -eq 0 ]]; then
 leap+=1
 fi
 
 if [[ $temp100 -eq 0 ]]; then
    if [[ $temp400 -eq 0 ]]; then
        leap=0
    fi
 fi
 
 if [[ $leap -eq 0 ]]; then
 local max_days=$(echo $list_of_days | awk -v awkvar="$i_month" '{ print $awkvar; }')
 else
  local max_days=$(echo $list_of_days_leap | awk -v awkvar="$i_month" '{ print $awkvar; }')
 fi
 
 local rand_day=$((1 + $RANDOM % $max_days))
 
 local rand_hour=$(($RANDOM % 25))
 if [[ $rand_hour -lt 10 ]]; then
 rand_hour=$(printf '%02d\n' "$rand_hour")
 fi
 local rand_minute=$(($RANDOM % 60))
 if [[ $rand_minute -lt 10 ]]; then
 rand_minute=$(printf '%02d\n' "$rand_minute")
 fi
 local rand_second=$(($RANDOM % 60))
 if [[ $rand_second -lt 10 ]]; then
 rand_second=$(printf '%02d\n' "$rand_second")
 fi
 
 echo "[$rand_day/$month/$rand_year:$rand_hour:$rand_minute:$rand_second +0000]"
 
}
 #https://*.com/
 
 function rand_url(){
 
 local list_of_urls="google github nginx ducksarethebest cat-bounce nohomophobes hosanna1"
 
 local i=$((1 + $RANDOM % 7 ))
 
 url=$(echo $list_of_urls | awk -v awkvar="$i" '{ print $awkvar; }')
 
 echo "https://$url.com/"
 
}

 function rand_agent(){

local list_of_agents=("Mozilla/5.0 (Macintosh; Intel Mac OS X 11.1; rv:84.0) Gecko/20100101 Firefox/84.0" "Opera/9.80 (Windows NT 6.2; Win64; x64) Presto/2.12.388 Version/12.17" "Opera/9.80 (X11; Linux i686; Ubuntu/14.10) Presto/2.12.388 Version/12.16.2" "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.75.14 (KHTML, like Gecko) Version/7.0.3 Safari/7046A194A" "Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; AS; rv:11.0) like Gecko" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.102 Safari/537.36 Edge/18.19582" "Googlebot/2.1 (+http://www.googlebot.com/bot.html)" "curl/7.64.1" "Safari/537.36 OPR/74.0.3911.218 (Edition Yx 05)")
                
                
local i=$(($RANDOM % 9))

echo "\"${list_of_agents[$i]}\" "
                
}
