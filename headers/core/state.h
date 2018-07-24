#ifndef STATE_h
#define STATE_h

#ifdef MAIN
#define EXTERN
#define IINIT = 0
#define BINIT =false
#define SINIT =""
#else
#define EXTERN extern
#define IINIT
#define SINIT
#define BINIT
#endif
#include <string>
#include <vector>
EXTERN bool NODE	  	BINIT;//work as node, ignore everything except verbose
EXTERN bool SERVER	  	BINIT;//work as server
EXTERN bool VERBOSE	  	BINIT;//verbose mode
EXTERN bool FORCE	  	BINIT;//forced mode
EXTERN int LANDMARK_RANGE 	IINIT;//how large of range to check in landmark alignment, 0=dissabled
EXTERN bool SMART	  	BINIT;//do smart landmarking
EXTERN bool HERUISTICS	  	BINIT;//use landmarking heruistics
EXTERN int SPLICE_LEVEL	  	IINIT;//what level of splice detection/fixing to use
EXTERN bool FIX_MODE	  	BINIT;//we are in fix mode, mutualy exclusive with -l
EXTERN int FIX_LEVEL	  	IINIT;//and this is the fix level
EXTERN bool ERROR_BRANCHING	BINIT;//branch on error
EXTERN std::string IN_PATH	SINIT;//path to dir containing files
EXTERN std::string OUT_PATH	SINIT;//path to dump files
EXTERN std::string CONVERT_TO 	SINIT;//what should we convert to 
EXTERN std::string SERVER_IP	SINIT;//ip of server
EXTERN int PORT			IINIT;//port used on server, used by both server and node

EXTERN std::vector<std::string> args;//the arg list passed to main
#endif
