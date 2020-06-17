#include<iostream>
using namespace std;
#include<cmath>
#include<stdlib.h>
#include<fstream>
#define END_TIME 10000
double rand_val() { //(0,1)までの一様乱数作成
	double a; 
	a = (rand() + 0.5) / (RAND_MAX + 1);
	return a;
}
double rnd_exp(double ramda) { //指数分布乱数作成
	return -log(1 - rand_val()) / ramda;
}
double kaijo(double x) {　//n!作成
	int num = x;
	if (num == 0) {
		return 1;
	}
	else {
		while (num > 1) {
			num = num - 1;
			x = x * num;
		}
		return x;
	}

}
struct poason { //それぞれの時刻における到達個数を記憶
	double count = 0;
};
int main() {
	ofstream ofs("第二回.csv"); //ファイルにデータを保存
	srand(18140024);
	double time = 0;
	int num = 0;
	double ramda = 2; //今回はramda=2
	poason A[END_TIME];
	while (time <= END_TIME) { //終了時刻までそれぞれの時刻の到達個数を記憶
		double x = rnd_exp(ramda);
		time += x;
		num += 1;
		A[int(time)].count += 1;
	}
	double sum = 0;
	double max = -1;
	double min = END_TIME;
	for (int i = 0; i < END_TIME; i++) {　//到達時刻を記憶、単位時間当たりの到達個数の最大最小を記憶
		ofs << A[i].count << endl;
		sum += A[i].count;
	    if (max < A[i].count)max = A[i].count;
	    if (min > A[i].count)min = A[i].count;
	}
	cout << max <<" "<< min << endl;
	double i = min;
	while (i <= max) { //最大値から最小値までのポアソン分布作成
		double k = kaijo(i);
		double p = exp(-ramda) * pow(ramda, i) / k;
		sum += p;
		cout << p << endl;
		i += 1;
	}
	cout << exp(-2) << endl;


}
