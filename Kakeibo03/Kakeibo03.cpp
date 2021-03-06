// Kakeibo03.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>

using namespace std;

class Kakeibo
{
protected:
	int zankin;

public:
	Kakeibo() { zankin = GetZankin(); }
	~Kakeibo() { SetZankin(); }
	void shunyu(int x) { zankin += x; }
	void shishutsu(int x) { zankin -= x; }
	void deisp_zankin()
	{
		cout << "残金: " << zankin << "円" << endl;
	}
	int GetZankin();
	void SetZankin();
};

int Kakeibo::GetZankin() {
	string zan;
	ifstream kakei_file("kakei.txt");
	if (!kakei_file) {
		return 0;
	}
	kakei_file >> zan;
	return(atoi(zan.c_str()));
}

void Kakeibo::SetZankin() {
	ofstream kakei_file("kakei.txt", ios_base::trunc);
	kakei_file << zankin;
}


class KakeiEx : public Kakeibo
{
	int kyuyo;
	int sonota_in;
	int shokuhi;
	int kosaihi;
	int sonota_out;
public:
	KakeiEx();
	~KakeiEx();
	void shishutsu_menu();
	void shunyu_menu();
	void disp_komoku();
};

KakeiEx::KakeiEx()
{
	ifstream kakei_file("kakeiex.txt");
	if (!kakei_file) {
		kyuyo = 0;
		sonota_in = 0;
		shokuhi = 0;
		kosaihi = 0;
		sonota_out = 0;
	} else {
		kakei_file >> kyuyo >> sonota_in >> shokuhi >> kosaihi
			>> sonota_out;
	}
}

KakeiEx::~KakeiEx()
{
	ofstream kakei_file("kakeiex.txt", ios_base::trunc);
	kakei_file << kyuyo << endl;
	kakei_file << sonota_in << endl;
	kakei_file << shokuhi << endl;
	kakei_file << kosaihi << endl;
	kakei_file << sonota_out << endl;
}

void KakeiEx::shunyu_menu() {
	string buf;
	int money;

	while (1) {
		cout << "(a)給与(b)その他の収入 --- ";
		getline(cin, buf);
		if (buf != "a" && buf != "b")
		{
			cout << "入力が不正です" << endl;
			continue;
		}
		switch (buf[0]) {
		case 'a':
			cout << "給与収入(円) --- ";
			getline(cin, buf);
			money = atoi(buf.c_str());
			kyuyo += money;
			shunyu(money);
			break;
		case 'b':
			cout << "その他の収入(円) --- ";
			getline(cin, buf);
			money = atoi(buf.c_str());
			sonota_in += money;
			shunyu(money);
			break;
		default:
			cout << "Error" << endl;
			break;
		}
		break;
	}
}

void KakeiEx::shishutsu_menu() {
	string buf;
	int money;

	while (1) {
		cout << "(a)食費 (b)交際費 (c)その他の支出 --- ";
		getline(cin, buf);
		if (buf != "a" && buf != "b" && buf !="c")
		{
			cout << "入力が不正です" << endl;
			continue;
		}
		switch (buf[0]) {
		case 'a':
			cout << "食費(円) --- ";
			getline(cin, buf);
			money = atoi(buf.c_str());
			shokuhi += money;
			shishutsu(money);
			break;
		case 'b':
			cout << "交際費(円) --- ";
			getline(cin, buf);
			money = atoi(buf.c_str());
			kosaihi += money;
			shishutsu(money);
			break;
		case 'c':
			cout << "その他の支出(円)";
			getline(cin, buf);
			money = atoi(buf.c_str());
			sonota_out += money;
			shishutsu(money);
			break;
		default:
			cout << "Error" << endl;
			break;
		}
		break;
	}
}

void KakeiEx::disp_komoku() {
	cout << "収入 *****************" << endl;
	cout << setw(15) << left << "給与収入";
	cout << setw(8) << right << kyuyo << endl;
	cout << setw(15) << left << "その他の収入";
	cout << setw(8) << right << sonota_in << endl;
	cout << "------------------" << endl;
	cout << setw(15) << left << "収入合計";
	cout << setw(8) << right << kyuyo + sonota_in << endl;
	cout << endl;
	cout << "支出 *****************" << endl;
	cout << setw(15) << left << "食費";
	cout << setw(8) << right << shokuhi << endl;
	cout << setw(15) << left << "交際費";
	cout << setw(8) << right << kosaihi << endl;
	cout << setw(15) << left << "その他の支出";
	cout << setw(8) << right << sonota_out << endl;
	cout << "-------------------------------" << endl;
	cout << setw(15) << left << "支出合計";
	cout << setw(8) << right << shokuhi + kosaihi  + sonota_out << endl;
	cout << endl;
}

int menu() {
	string ret;
	cout << "1:収入 2:支出 3:残金表示 4:項目別表示 0:終了 -----";
	getline(cin, ret);
	return (ret[0] - '0');
}

int main()
{
	KakeiEx mykakeiex;
	int ans;
	bool loopend = false;

	cout << "猫でもわかる家計簿 --------------" << endl;
	cout << endl;

	while (1) {
		ans = menu();
		switch (ans) {
		case 0:
			loopend = true;
			break;
		case 1:
			mykakeiex.shunyu_menu();
			break;
		case 2:
			mykakeiex.shishutsu_menu();
			break;
		case 3:
			mykakeiex.deisp_zankin();
			break;
		case 4:
			mykakeiex.disp_komoku();
			break;
		default:
			cout << "入力が不正です" << endl;
			break;
		}
		if (loopend)
			break;
	}
	return 0;
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
