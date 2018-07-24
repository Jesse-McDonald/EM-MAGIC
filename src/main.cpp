#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <src.h>
#define MAIN
#include <state.h>

using namespace std;
void help(){
	cout<<"help file comming in the future, for now just look at programFlow.txt in the github for EM-MAGIC"<<endl;
}
int main(int argc, char* argv[]){
	args= vector<string>();
	for(int i =0; i<argc;i++){
		args.push_back(string(argv[i]));
		//cout<<args[i]<<endl;
	}
	for(int i=1;i<args.size();i++){//yah, I know, same loop but it is important becuase we have converted everything to std::string
		if(args[i]=="-h"){
			help();
			return 0;
		}else if(args[i]=="-n"){
			NODE=true;
			if(SERVER){
				cout<<"ERROR: -n is not compatable with -s"<<endl;
				return 128;
			}
			i++;//move on to first arg of -n
			if(i>=args.size()||args[i][0]=='-'){
				cout<<"ERROR: Insufficient arguments for -n\nSyntax is '-n <SERVER> <PORT>'"<<endl;
				return 128;
			}
			SERVER_IP=args[i];
			
			i++;//move on to second arg of -n
			if(i>=args.size()||args[i][0]=='-'){
				cout<<"ERROR: Insufficient arguments for -n\nSyntax is '-n <SERVER> <PORT>'"<<endl;
				return 128;
			}
			try{
				PORT=stoi(args[i]);
			}catch(...){	
				cout<<"ERROR: Invalid argument <PORT>, could not convert to port number"<<endl;
				return 128;
			}
	
		}else if(args[i]=="-sm"){
			SERVER=true;
			if(NODE){
				cout<<"-s is not compatable with -n"<<endl;
				return 128;
			}
			i++;//move on to first arg of -s
			if(i>=args.size()||args[i][0]=='-'){
				cout<<"ERROR: Insufficient arguments for -s\nSyntax is '-s <PORT>'"<<endl;
				return 128;
			}
			try{
				PORT=stoi(args[i]);
			}catch(...){	
				cout<<"ERROR: Invalid argument <PORT>, could not convert to port number"<<endl;
				return 128;
			}
		}else if(args[i]=="-v"){
			VERBOSE=true;
		}else if(args[i]=="-f"){
			FORCE=true;
		}else if(args[i]=="-i"){
			i++;//move on to second arg of -i

			if(i>=args.size()){
				cout<<"ERROR: Insufficient arguments for -i\nSyntax is '-i <DIR>'"<<endl;
				return 128;
			}
			struct stat info;
			if(stat(args[i].c_str(),&info)!=0){
				cout<<"ERROR: Directory "<<args[i]<<" not found"<<endl;
				return 128;
			}else if(!( info.st_mode & S_IFDIR )){
				cout<<"ERROR: "<<args[i]<<" is a file, not a directory"<<endl;
				return 128;
			}
			IN_PATH=args[i];
		}else if(args[i]=="-o"){
			i++;//move on to second arg of -o

			if(i>=args.size()){
				cout<<"ERROR: Insufficient arguments for -o\nSyntax is '-o <DIR>'"<<endl;
				return 128;
			}
			struct stat info;
			if(stat(args[i].c_str(),&info)!=0){
				cout<<"ERROR: Directory "<<args[i]<<" not found"<<endl;
				return 128;
			}else if(!( info.st_mode & S_IFDIR )){
				cout<<"ERROR: "<<args[i]<<" is a file, not a directory"<<endl;
				return 128;
			}
			OUT_PATH=args[i];
		}else if(args[i]=="-c"){
			i++;//move on to second arg of -c

			if(i>=args.size()){
				cout<<"ERROR: Insufficient arguments for -c\nSyntax is '-c <OUTPUT>'"<<endl;
				return 128;
			}
			CONVERT_TO=args[i];
			//check later if we support this option
		}else if(args[i]=="-l"){
			LANDMARK_RANGE=-1;
			i++;
			if(i<args.size()){
				try{
					LANDMARK_RANGE=stoi(args[i]);
				}catch(...){	
					cout<<"WARNING: No range specified for landmark alignment (-l)\nDefaulting to full image scan, this could take quite a while"<<endl;
					LANDMARK_RANGE=-1;
					i--;
				}
			
			}else{
				cout<<"WARNING: No range specified for landmark alignment (-l)\nDefaulting to full image scan, this could take quite a while"<<endl;
				i--;
			}
		}else if(args[i]=="-s"){
			SMART=true;

		}else if(args[i]=="-he"){
			HERUISTICS=true;

		}else if(args[i]=="-sd"){
			SPLICE_LEVEL=1;

		}else if(args[i]=="-sc"){
			SPLICE_LEVEL=2;

		}else if(args[i]=="-se"){
			SPLICE_LEVEL=3;

		}else if(args[i]=="-eb"){
			ERROR_BRANCHING=true;

		}else if(args[i]=="-fix"){
			i++;
			FIX_MODE=true;
			if(i<args.size()){
				try{
					FIX_LEVEL=stoi(args[i]);
				}catch(...){	
					FIX_LEVEL=0;	
					i--;				
				}
			
			}else{
				i--;
			}

		}else{
			cout<<"ERROR: Unknown argument "<<args[i]<<endl;
			return 128;
		}
	}
	if(FORCE&&!SERVER){
		cout<<"WARNING: -f only applicable in server mode, argument ignored"<<endl;
	}
	if(LANDMARK_RANGE==0&&SMART){
		cout<<"WARNING: -s only applicable in -l is specified, argument ignored"<<endl;
	}
	if(LANDMARK_RANGE==0&&ERROR_BRANCHING){
		cout<<"WARNING: -eb only applicable in -l is specified, argument ignored"<<endl;
	}
	if(HERUISTICS&&LANDMARK_RANGE==0){
		cout<<"WARNING: -he only applicable in -l is specified, argument ignored"<<endl;
	}
	if(LANDMARK_RANGE!=0&&FIX_MODE){
		cout<<"WARNING: both -fix and -l specified, entering fix mode and ignoring landmark alignment"<<endl;
	}
	if((NODE&&args.size()>5&&VERBOSE)||(NODE&&args.size()>4&&!VERBOSE)){
		cout<<"WARNING: -v is the only argument -n uses, all others ignored"<<endl;
	}
	if(!NODE&&IN_PATH.length()<1){
		cout<<"ERROR: No input directory specified, use '-i <DIR>'"<<endl;
		return 128;
	}
	if(!NODE&&OUT_PATH.length()<1){
		cout<<"ERROR: No output directory specified, use '-o <DIR>'"<<endl;
		return 128;
	}
	return startProcessing();
}

