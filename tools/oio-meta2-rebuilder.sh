#!/bin/bash

# oio-meta2-rebuilder.sh
# Copyright (C) 2016-2017 OpenIO SAS, original work as part of OpenIO SDS
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

#set -x

usage() {
	echo "Usage: `basename $0` -r ip_redis_host:redis_port -n namespace"
	echo "Example: `basename $0` -r 192.120.17.12:6051 -n OPENIO " ;
	exit
}

[ $# -ne 4 ] && usage

# trap ctrl-c and call ctrl_c()
trap ctrl_c INT

function ctrl_c() {
	echo "Stop processing ..."
	kill $$
}

while getopts ":r:n:" opt; do
  case $opt in
    r)
      echo "-r was triggered, Parameter: $OPTARG" >&2
      REDIS_HOST=${OPTARG/:*/}
      REDIS_PORT=${OPTARG/*:/}
      if [[ $REDIS_HOST == "" ]]
          then
          echo "Missing  ip_redis_host"
	  exit 1
      fi
      if [[ $REDIS_PORT == "" ]]
	  then
	      echo "Missing  redis_port"
	      exit 1
      fi
      ;;
    n)
      echo "-n was triggered, Parameter: $OPTARG" >&2
      NAMESPACE=$OPTARG
      ;;
     *)
	usage
	exit 0
      ;;
  esac
done


#Get account list
redis_bin=$(which redis-cli)
ACCOUNT_LIST=$(${redis_bin} -h $REDIS_HOST -p $REDIS_PORT  keys account:* | sed 's@.*account:\(.*\)@\1@' | tr "\n" " ")

clear

#Launch meta2 repair
posit=0
for account in $ACCOUNT_LIST
do
	export OIO_NS=${NAMESPACE} && export OIO_ACCOUNT=$account
	CMAX=$(openio container list -f value -c Name --full | wc -l)
	echo "Treatment $CMAX containers for account $account"
	export tempnum=0
	openio container list -f value -c Name --full \
	| while read REF
	do
	    tput cup $((posit+1)) 0 >&2
	    echo "container set $REF --property sys.last_rebuild=$(date +%s)"
	    tput cup $((posit+1)) 0 >&2
	    echo "$((++tempnum))/$CMAX" >&2
	done | openio
	posit=$((posit+2))
	tput cup $posit 0 >&2
done
