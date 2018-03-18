#ifndef context_hpp
#define context_hpp

#include <string>
#include <iostream>

#include <unordered_map>

#include <stdexcept>

// class context{
//   public:
//     stackpointer;
//     framepointer;
//     function to adjust stack pointer at beginnign
//     function to create return
//     function for label creation etc
  
//   private:


// }


typedef int Tscopenum;
typedef int Toffset;
typedef std::string TVarName;


class context{
private:
	int destReg;
	int nReg;
	int lcount;
	std::unordered_map<Tscopenum, std::unordered_map<TVarName, Toffset> > VarMap;
	int FrameSize;
	int ParamPass;
	int ScopeNum;

public:
	context(int _destReg, int _nReg, int _lcount,
	std::unordered_map<Tscopenum, std::unordered_map<TVarName, Toffset>> _VarMap,
	int _FrameSize, int _ParamPass, int _ScopeNum);
	
	//--------------------Registers-----------------------
	void assignReg();
	void freeReg();
	void setdestReg(int dest);
	void setnReg(int reg);
	int getnReg();
	int getdestReg();

	//--------------------Labels-----------------------
	std::string createLabel();

	//--------------------Frames-----------------------
	void incFrameSize();
	int getFrameSize();


  //-------------------Passing parameters------------------------
	void incrParamPass();
	void resetParamPass();
	int get_ParamPass();

	//--------------------Variables-----------------------
	void addVartoScope(std::string name, int offset);
	int getVarOffset(std::string name);
	bool isVarinScope(std::string name);
	void deleteScope();
	void incrScope();
	void decrScope();


};


// class context{
// private:
// 	int destReg;
// 	int nReg;
// 	int lcount;
// 	std::unordered_map<std::string, int> localMap;
// 	int FrameSize;
// 	int ParamPass;

// public:
// 	context(int _destReg, int _nReg, int _lcount, 
// 	  std::unordered_map<std::string, int> _localMap, int _FrameSize, int _ParamPass);
	
// 	//General Register functions
// 	void assignReg();
// 	void freeReg();

// 	//specific regfunctions
// 	void setdestReg(int dest);
// 	void setnReg(int reg);
// 	int getnReg();
// 	int getdestReg();

// 	//label function
// 	std::string createLabel();


// 	//map functions
// 	bool checkVar(std::string name); -- 
// 	void incFrameSize();
// 	int getFrameSize();

// 	void addlocal(std::string name, int offset); -- 
// 	int getlocalOffset(std::string name); ---
// 	void incrParamPass();
// 	void resetParamPass();
// 	int get_ParamPass();

// };


#endif