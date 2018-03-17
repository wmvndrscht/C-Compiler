#ifndef context_hpp
#define context_hpp

#include <string>
#include <iostream>

#include <unordered_map>


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
	std::unordered_map<std::string, int> localMap;
	int FrameSize;
	int ParamPass;

public:
	context(int _destReg, int _nReg, int _lcount, 
	  std::unordered_map<std::string, int> _localMap, int _FrameSize, int _ParamPass);
	
	//General Register functions
	void assignReg();
	void freeReg();

	//specific regfunctions
	void setdestReg(int dest);
	void setnReg(int reg);
	int getnReg();
	int getdestReg();

	//label function
	std::string createLabel();


	//map functions
	bool checkVar(std::string name);
	void incFrameSize();
	int getFrameSize();
	void addlocal(std::string name, int offset);
	int getlocalOffset(std::string name);
	void incrParamPass();
	void resetParamPass();
	int get_ParamPass();

};

#endif