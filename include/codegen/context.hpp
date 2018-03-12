#ifndef context_hpp
#define context_hpp

#include <string>
#include <iostream>

// class context{
//   public:
//     stackpointer;
//     framepointer;
//     function to adjust stack pointer at beginnign
//     function to create return
//     function for label creation etc
  
//   private:


// }



class context{
private:
	int destReg;
	int nReg;
	int lcount;
public:
	context(int _destReg, int _nReg, int _lcount);
	void assignReg();
	void freeReg();
	void setdestReg(int dest);
	void setnReg(int reg);
	int getnReg();
	int getdestReg();
	std::string createLabel();

};

#endif