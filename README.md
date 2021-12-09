# RAFT

### Instructions to run the program:
I have written 2 shell scripts - one to run the client program and other to run the server program. To run the program on a local machine, set the variable *local*  to 1 in the script. The scripts support running of 3 server network and 5 server, and you can change the configuration by changing the variable *num* in the script. 

## Server:
        1. run the script with title - "Raft_server.sh" as:  ./Raft_server.sh [server ID] [repeat([peer ID])] [server role]
        2. Server role parameter accepts three types of roles: 
                0 - Follower, 
                1 - Candidate,  
                2 - Leader
        3. For example, ./Raft-server.sh 36 37 38 39 40 1 
        This starts a candidate node with ID: 36 with 4 peers of IDs: 37, 38, 39, 40. 

## Client:
        1. run the script with title - "raft_client.sh" as: 
                ./raft_client.sh [repeat(server ID)] [number of customers] [number of orders for each customer] [request type]
        2. Requests type can be 
                1 - Write Request, 
                2 - Read Request, 
                4 - Fetch Leader ID Request
        3. For example: given the server program above, we can run ./raft-client.sh 36 37 38 39 40 4 100 2
        Here, 4 represents number of customers, 100 represents number of orders for each customer, and 2 represents the request type
       
   
## Notes on running on the Khoury VDI cluster: 
> Since all the vdi machines belongs to a cluster, all the machines have the ip address ending with "10.200.125.", the last 2 digits represents the id of a machine, and we have used that to represent server id as the command line argument to run the script. 
 


