#!/bin/sh
#total number of nodes: 5

# argv[1]: $1 is id of self
# argv[i]: i^th node id for i = 2, 3, 4, 5
# argv[6]: port option (to deal with port in use problem): 1 or 2


echo Creating server with node id $1  \
		 with	peer node ids: $2 $3 $4 $5

if [ $6 -eq 1 ]; then
	./server "10100$2" $2 $1 \
						$3 "10.200.125.$3" "10100$3" \
						$4 "10.200.125.$4" "10100$4" \
						$5 "10.200.125.$5" "10100$5" \
						$6 "10.200.125.$6" "10100$6"

elif [ $6 -eq 2 ]; then
		./server "10100$2" $2 $1 \
							$3 "10.200.125.$3" "10100$3" \
							$4 "10.200.125.$4" "10100$4" \
							$5 "10.200.125.$5" "10100$5" \
							$6 "10.200.125.$6" "10100$6"
fi
