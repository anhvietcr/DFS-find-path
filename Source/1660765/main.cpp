#include "DFS.h"

int main(int argc, char* argv[])
{
	DFS dfs;

	dfs.init(argv[1]);
	dfs.Graph();
	dfs.Result(argv[2]);
}