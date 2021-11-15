#ifndef __SERVERTHREAD_H__
#define __SERVERTHREAD_H__

#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <map>

#include "Messages.h"
#include "ServerSocket.h"


struct AdminRequest {
	LaptopInfo laptop;
	std::promise<LaptopInfo> prom;
};

struct ServerInfo{
	int unique_id;
	std::string IP;
	int port;
};


struct Log{
	MapOp command;
	int term;
};

class LaptopFactory {
private:
	//Persistent state on all servers: Updated on stable storage before responding to RPCs
	int currentTerm;  									// latest term server has seen (initialized to 0 on first boot, increases monotonically)
	int votedFor; 											//candidateId that received vote in current term (or -1 if none)
	//std::vector<Log> smr_log;						//log entries; each entry contains command for state machine,
																			//and term when entry was received by leader (first index is 1)

  //Volatile state on all servers:
	int committed_index;	//index of highest log entry known to be committed (initialized to 0, increases monotonically)
 	int last_log_index;


	std::vector<MapOp> smr_log;


	//-------------------------------------------------------------------------//

	//information about the other server nodes
	int num_peers;
	std::vector<ServerInfo> PeerServerInfo;

	int node_id;
	int leader_id;



	std::mutex MapRecord_lock;
	std::map<int, int> MapCustomerRecord;



	//admin request queue
	std::queue<std::unique_ptr<AdminRequest>> erq;
	std::mutex erq_lock;
	std::condition_variable erq_cv;

	LaptopInfo CreateLaptop(CustomerRequest order, int engineer_id);
public:
	LaptopFactory();

	void EngineerThread(std::unique_ptr<ServerSocket> socket, int id);
	void AdminThread();

	int FillPeerServerInfo(int argc, char* argv[]);
	void Fill_Customer_Record(CustomerRequest * request, CustomerRecord * record);

	void SetNumPeers(int num);
	void SetFactoryId(int id);
	void Init_Socket_Status(int * status);

	void Handle_Replication_Request(ReplicationRequest * rep_req);
	void Apply_Committed_Op();


};
#endif // end of #ifndef __SERVERTHREAD_H__
