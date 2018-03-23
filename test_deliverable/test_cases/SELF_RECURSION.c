int f(int a){

	if(a < 1){
		return 2;
	}
	else{
		return a + f(a-1);
	}
	
}