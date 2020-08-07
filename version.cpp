#define RCSTREE_VERSION_STR "0.1.0"
#define RCSTREE_REMARK_STR  "Create project for RCSTree config tool. by wl 2020-06-17,V0.1.0."

#include "version.h"

//打印版本信息函数
bool echoVersion(int argc, char *argv[]){
	for(int i = 0;i < argc;i++){
		if(qstricmp(argv[i],"-v") == 0 || qstricmp(argv[i],"--version") == 0 ){
			std::cout << "Version: " << RCSTREE_VERSION_STR << std::endl;
			std::cout << "Remark : " << RCSTREE_REMARK_STR  << std::endl;	
			return true;
		}
	}
	return  false;
}