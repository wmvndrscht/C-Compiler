int f(){
    int a =2;
    int b =1;

    if(a<b){
        a=a-1;
        if(a>b){
            b=b+3;
            if(a==b){
                return a*b;
            }
        }
        return b;
    }
    return 13;
}