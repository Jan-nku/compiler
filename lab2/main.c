//输入一个数作为斐波那契数列的输入，输出斐波那契数列的值
//输入和输出使用的是SysY定义的库函数
//斐波那契数列
int fib(int x){
	if(x == 1){
		return 1;
	}
	else{
		return x*fib(x-1);
	}
}

int main(){
	int t;
	t = getint();
	putint(fib(t));
}