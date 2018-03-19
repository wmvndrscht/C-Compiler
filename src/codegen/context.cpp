#include "../../include/codegen/context.hpp"



context::context(int _destReg, int _nReg, int _lcount,
	std::unordered_map<Tscopenum, std::unordered_map<TVarName, Toffset>> _VarMap,
	int _FrameSize, int _ParamPass, int _ScopeNum) :
	destReg(_destReg), nReg(_nReg), lcount(_lcount), VarMap(_VarMap),
	FrameSize(_FrameSize), ParamPass(_ParamPass), ScopeNum(_ScopeNum){}


//--------------------Registers-----------------------

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


//--------------------Labels-----------------------


std::string context::createLabel(){
	lcount+=1;
	return std::string("L")+std::to_string(lcount);
}


//--------------------Frames-----------------------


void context::incFrameSize(){
	FrameSize+=4;
}

int context::getFrameSize(){
	return FrameSize;
}


//-------------------Passing parameters------------------------


void context::incrParamPass(){
	ParamPass++;
}

void context::resetParamPass(){
	ParamPass = 0;
}

int context::get_ParamPass(){
	return ParamPass;
}

//--------------------Variables-----------------------

//1!!!!Check this is valid!!!! below
void context::addVartoScope(std::string name, int offset){
	// VarMap.insert(std::make_pair(ScopeNum,std::make_pair(name,offset)));
	//this is insert
	VarMap[ScopeNum][name] = offset;
}

int context::getVarOffset(std::string name){
	//go backwards finding variable definition
	//assumed already checked for global
	bool found = false;
	int i = ScopeNum;


	while(i > 0 && !found){

		auto got = VarMap[i].find(name);
		if( !(got ==  VarMap[i].end() )){
			return VarMap[i][name];
			found = true;
		}
		i--;
	}

	throw std::runtime_error("getVarOffset did not occure");
	return -1;

}




bool context::isVarinScope(std::string name){
	return ((VarMap[ScopeNum]).count(name) > 0);
}

void context::deleteScope(){
	VarMap.erase(ScopeNum);

}

void context::incrScope(){
	ScopeNum++;
}

void context::decrScope(){
	ScopeNum--;
}

int context::getScopeNum(){
	return ScopeNum;
}


bool context::isVarGlobal(std::string name){
	bool found = false;
	int i = ScopeNum;


	while(i > 0 && !found){

		auto got = VarMap[i].find(name);
		if( !(got ==  VarMap[i].end() )){
			return false;
			found = true;
		}
		i--;
	}
	return true;

}