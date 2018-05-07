#include "DFS.h"



DFS::DFS()
{
	
}


DFS::~DFS()
{
}

void DFS::init(char * input)
{

	std::ifstream in(input, std::ios::in);
	
	in >> this->start >> this->end >> this->soDinh >> this->soCanh;

	//init array chua cac dinh
	duongDi = new int*[this->soCanh];
	for (int i = 0; i < this->soCanh; i++) {
		duongDi[i] = new int[2];
	}
	
	//init array chua ten duong di
	tenDuong = new std::string[this->soCanh];

	//init array chua do dai duong di
	doDai = new float[this->soCanh];
	
	//read input
	for (int i = 0; i < this->soCanh; i++) {
		in >> duongDi[i][0];
		in >> duongDi[i][1];
		in >> tenDuong[i];
		in >> doDai[i];
	}

	//khoi tao ma tran ke
	dinh = new float*[this->soDinh];
	for (int i = 0; i < this->soDinh; i++) {
		dinh[i] = new float[this->soDinh];
	}
	for (int i = 0; i < this->soDinh; i++) {
		for (int j = 0; j < this->soDinh; j++) {
			dinh[i][j] = 0;
		}
	}

	//init mang danh dau va chua xet
	this->chuaxet = new bool[this->soDinh];
	this->danhDauTruoc = new int[this->soDinh];
	for (int i = 0; i < this->soDinh; i++) {
		this->danhDauTruoc[i] = 0;
		this->chuaxet[i] = true;
	}

	// tao ma tran trong so
	for (int i = 0; i < this->soCanh; i++) {
		for (int j = 0; j < this->soDinh; j++) {
			for (int k = 0; k < this->soDinh; k++) {
				if (j == duongDi[i][0] && k == duongDi[i][1]) {
					dinh[j][k] = doDai[i];
				}
				if (j == duongDi[i][1] && k == duongDi[i][0]) {
					dinh[j][k] = doDai[i];
				}
			}
		}
	}
	in.close();
}

void DFS::Graph()
{
	// Khởi tạo ngăn xếp
	std::stack<int> s;

	// Thêm start vào ngăn xếp
	s.push(this->start);

	while (!s.empty()) {
		int v = s.top(); s.pop();

		// Neu trung voi dinh end
		if (v == this->end) break;
		if (chuaxet[v] == false) continue;
		else {
			// Danh dau da vieng tham v
			chuaxet[v] = false;

			// Do dai doan duong dau tien va vi tri 
			float minimumDoDai = 0;
			int index = 0;

			//Tim vi tri va do dai duong di dau tien
			for (int i = 0; i < this->soDinh; i++) {
				if (dinh[v][i] != 0 && chuaxet[i]) {
					minimumDoDai = dinh[v][i];
					index = i;
					break;
				}
			}

			// Duyet qua cac dinh i co canh noi voi v
			for (int i = index; i < this->soDinh; i++) {
				if (dinh[v][i] != 0 && chuaxet[i]) {
					if ((dinh[v][i] - minimumDoDai) < 0) {
						minimumDoDai = dinh[v][i];
						index = i;
					}
				}
			}

			// Neu != default value 
			if (minimumDoDai && index) {
				danhDauTruoc[index] = v;
				s.push(index);
				soKm += minimumDoDai;
			}
		}
	}
}

void DFS::Result(char * output)
{
	std::ofstream out(output);
	if (0 == danhDauTruoc[end]) {
		std::cout << "NULL";
		out << -1;
		return;
	}

	// so Km cua quang duong di
	std::cout << this->soKm << "\n";
	out << this->soKm << "\n";

	// tim ten duong di
	for (int t = end; t != start; t = danhDauTruoc[t]) {
		for (int i = 0; i < this->soCanh; i++) {
			if ((duongDi[i][0] == t && duongDi[i][1] == danhDauTruoc[t])
				|| (duongDi[i][0] == danhDauTruoc[t] && duongDi[i][1] == t)) {
				stackDuongDi.push(tenDuong[i]);
			}
		}
	}

	// xuat ket qua
	while (!stackDuongDi.empty()) {
		std::cout << stackDuongDi.top();
		out << stackDuongDi.top();
		stackDuongDi.pop();
		if (!stackDuongDi.empty()) {
			std::cout << " -> ";
			out << " -> ";
		}
	}

	out.close();
}