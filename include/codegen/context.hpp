#ifndef ast_context_hpp
#define ast_context_hpp

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
	int lReg;
	int rReg;
	int availReg;
public:
	context(int _destReg, int _lReg, int _rReg, int _availReg): 
	destReg(_destReg), lReg(_availReg), rReg(_rReg), availReg(_availReg){}
	
	void assignReg(){
		if( availReg == 3){
			lReg = 3;
			rReg = 8;
			availReg = 8;
			return;
		}
		else if( 7 < availReg && availReg < 15){
			lReg = availReg;
			rReg = availReg+=1;
			availReg+=1;
			return;
		}
		else if(availReg == 15){
			lReg = 15;
			rReg = 24;
			availReg = 24;
			return;
		}
		else if(availReg == 24){
			lReg = 24;
			rReg = 25;
			availReg+=1;
			return;
		}
		else{
			std::cerr << "**Reached bounds of availReg**" << std::endl;
			exit(-1);
		}
	}

	void freeReg(){
		if(availReg == 3){
			return;
		}
		else if( (8 < availReg && availReg < 16) || availReg == 25){
			availReg-=1;
			return;
		}
		else if( availReg == 8){
			availReg = 3;
			return;
		}
		else if(availReg == 24){
			availReg=15;
			return;
		}
		else{
			std::cerr << "**freeReg error**" << std::endl;
			exit(-1);
		}
	}

	void setdestReg(int dest){
		destReg = dest;
	}
	void setlReg(int reg){
		lReg = reg;
	}
	int getlReg(){
		return lReg;
	}
	int getrReg(){
		return rReg;
	}
	int getdestReg(){
		return destReg;
	}


};

#endif