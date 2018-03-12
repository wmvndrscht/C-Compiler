#include "../../include/codegen/context.hpp"



context::context(int _destReg, int _nReg, int _lcount) :
	destReg(_destReg), nReg(_nReg), lcount(_lcount){}


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