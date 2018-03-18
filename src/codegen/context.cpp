#include "../../include/codegen/context.hpp"



context::context(int _destReg, int _nReg, int _lcount,
	std::unordered_map<std::string, int> _localMap, int _FrameSize, int _ParamPass) :
	destReg(_destReg), nReg(_nReg), lcount(_lcount), localMap(_localMap),
	FrameSize(_FrameSize), ParamPass(_ParamPass){}


void context::assignReg(){
	if( nReg == 2){
		nReg = 3;
		return;
	}
	else if(nReg == 3){
		nReg = 8;
	}
	else if(nReg > 7 && nReg <15 ){
		nReg +=1;
		return;
	}
	else if(nReg == 15){
		nReg = 24;
		return;
	}
	else if(nReg == 24){
		nReg = 25;
		return;
	}
	else{
		std::cerr << "**Reached bounds of availReg**" << std::endl;
		exit(-1);
	}

}

void context::freeReg(){
	if(nReg == 3){
		nReg = 2;
		return;
	}
	else if(nReg == 8){
		nReg = 3;
	}
	else if( 8 < nReg && nReg < 16 ){
		nReg -=1;
		return;
	}
	else if( nReg == 24){
		nReg = 15;
		return;
	}
	else if(nReg == 25){
		nReg =24;
	}
	else{
		std::cerr << "**freeReg error**" << std::endl;
		exit(-1);
	}
}

void context::setdestReg(int dest){
	destReg = dest;
}
void context::setnReg(int reg){
	nReg = reg;
}
int context::getnReg(){
	return nReg;
}
int context::getdestReg(){
	return destReg;
}

std::string context::createLabel(){
	lcount+=1;
	return std::string("L")+std::to_string(lcount);
}

//FrameStack stuff



//
bool context::checkVar(std::string name){
	return (localMap.count(name) > 0);
}

void context::incFrameSize(){
	FrameSize+=4;
}

int context::getFrameSize(){
	return FrameSize;
}

void context::addlocal(std::string name, int offset){
	localMap.insert(std::make_pair(name,offset));
}

int context::getlocalOffset(std::string name){
	return localMap[name];
}

void context::incrParamPass(){
	ParamPass++;
}

void context::resetParamPass(){
	ParamPass = 0;
}

int context::get_ParamPass(){
	return ParamPass;
}