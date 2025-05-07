#include "FileFactory.h"


static IFile* OpenFile(std::string path,std::string mode){
    IFile* wIFile=nullptr;
    if(path.find(".bin",path.length()-4)){
        wIFile=new BinaryFile(path,mode);
    }
    else if(path.find(".csv",path.length()-4)){

    }
    return wIFile;
}