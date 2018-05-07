#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stack>

class DFS
{
private:
	int soDinh, soCanh;
	int start, end;
	
	int **duongDi;
	float **dinh;
	int *danhDauTruoc;
	bool *chuaxet;
	std::string *tenDuong;
	float *doDai;
	std::stack<std::string> stackDuongDi;
	float soKm = 0;

public:
	DFS();
	~DFS();
	void init(char*);
	void Graph();
	void Result(char*);
};

