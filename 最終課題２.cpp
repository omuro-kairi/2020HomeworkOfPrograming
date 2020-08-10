#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <math.h>
#include <random>
#include <chrono>
#include <cassert>

using namespace std;
using namespace std::chrono;


class Point {
	double X;
	double Y;

public:
	void setX(const double& newX) { X = newX; }
	double getX() { return X; }
	void setY(double newY) { Y = newY; }
	double getY() { return Y; }

};


double distance(double x1, double y1, double x2, double y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


int permutation(int k) {
	int sum = 1;
	for (int i = 1; i <= k; ++i){
		sum *= i;
	}
	return sum;
}

int main() {
	int PointNum = 4;//点の数を指定する
	int accuracy = PointNum*PointNum;//大きければ大きいほど精度が増すが時間がかかる。ここでは点の数の２乗によって比例させるものとする

	assert(accuracy > 0);
	assert(PointNum > 2);

	cout << "計算に時間がかかる場合があるのでそのままお待ちください" << endl << endl;
	auto t0 = high_resolution_clock::now();

	int num = PointNum - 1;

	vector<Point> P(PointNum);//各点の座標を定義
	P.emplace_back();
	P[0].setX(1.0);
	P[0].setY(1.0);
	P[1].setX(2.0);
	P[1].setY(2.0);
	P[2].setX(3.0);
	P[2].setY(3.0);
	P[3].setX(4.0);
	P[3].setY(4.0);
	/*P[4].setX(5.0);
	P[4].setY(5.0);
	P[5].setX(6.0);
	P[5].setY(6.0);
	P[6].setX(7.0);
	P[6].setY(7.0);
	P[7].setX(8.0);
	P[7].setY(8.0);
	P[8].setX(9.0);
	P[8].setY(9.0);*/


RN://vectorであるPの中身をランダムに入れ替える
	random_device get_rand_dev;
	mt19937 get_rand_mt(get_rand_dev());
	shuffle(P.begin(), P.end(), get_rand_mt);


	for (int j = 0; j <= num; j++) {//たまに入力していないのにP[n].X=0やP[n].Y=0となるのでそれを防ぐための処理
		
		if (P[j].getX() == 0 || P[j].getY() == 0) {
			goto RN;
		}
	}

	vector<double> vecofdissum(permutation(num) * accuracy);
	int count = 1;
	double distancesum = 0;
	int veccount = 0;

	while (count <= permutation(num) * accuracy) {

	RN2://分散させる為に再度シャッフルする
		mt19937 get_rand_mt(get_rand_dev());//vector Pの各オブジェクトの入れ替え
		shuffle(P.begin(), P.end(), get_rand_mt);


		for (int j = 0; j <= num; j++) {//たまに入力していないのにP[n].X=0やP[n].Y=0となるのでそれを防ぐための処理
			if (P[j].getX() == 0 || P[j].getY() == 0) {
				goto RN2;
			}
		}
		

		for (int n = 0; n <= num - 1; n++) {//1回の乱数における点同士の距離の合計
			int b = n+1;
			distancesum += distance(P[n].getX(), P[n].getY(), P[b].getX(), P[b].getY());

			}

		vecofdissum[veccount] = distancesum;

		count++;
		veccount++;
		distancesum = 0;

	}

	auto min = min_element(vecofdissum.begin(), vecofdissum.end());
	auto max = max_element(vecofdissum.begin(), vecofdissum.end());

	auto t1 = high_resolution_clock::now();

	cout << PointNum << "個の点を結んだ距離の" << endl;
	cout << "最小値:" << *min << endl;
	cout << "最大値:" << *max << endl << endl;
	cout << "計算時間　" << duration_cast<milliseconds>(t1 - t0).count() / 1000. << " s" << endl;
}




