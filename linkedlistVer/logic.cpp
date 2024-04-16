#include "logic.h"

bool findPath(headerList *board, int row, int col, int x1, int x2, int y1, int y2){
    if (traceH(board, x1)->size < y1 || traceH(board, x2)->size < y2)
        return false;

    if (trace(traceH(board, x1)->head, y1)->key != trace(traceH(board, x2)->head, y2)->key
        || trace(traceH(board, x1)->head, y1)->key == 0
        || trace(traceH(board, x2)->head, y2)->key == 0)
        return false;

    //Tạo graph
    vector<vector<int>> graph(row + 2, vector<int>(col + 2, 0));
	for (int i = 1; i <= row ; i++)
	{
        bool flag = true;
		for (int j = 1; j <= col; j++)
		{
            if (flag)
            {
                if (traceH(board, i) != nullptr && trace(traceH(board, i)->head, j) != nullptr)
                {
                    graph[i][j] = (trace(traceH(board, i)->head, j)->key != 0);
                }
                else{
                    flag = false;
                    graph[i][j] = 0;
                }
            }
            else
            {
                graph[i][j] = 0;
            }
		}
	}
    pair<int, int> start = {x1, y1};
    pair<int, int> end = {x2, y2};

    //BFS
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};
    deque<pair<int, int>> q;
    vector<vector<pair<int, int>>> trace(row + 2, vector<pair<int, int>>(col + 2, make_pair(-1, -1)));

    q.push_back(end);
    trace[end.first][end.second] = make_pair(-2, -2);
	graph[start.first][start.second] = 0;
	graph[end.first][end.second] = 0;
    while (!q.empty()) {
		auto u = q.front();
		q.pop_front();
		if (u == start) break;
		for (int i = 0; i < 4; ++i) {
			int x = u.first + dx[i];
			int y = u.second + dy[i];
			while (x >= 0 && x < row + 2 && y >= 0 && y < col + 2 && graph[x][y] == 0) {
				if (trace[x][y].first == -1) {
					trace[x][y] = u;
					q.push_back({ x, y });
				}
				x += dx[i];
				y += dy[i];
			}
		}
	}

    //Truy vết ngược về
    vector<pair<int, int>> route;
	if (trace[start.first][start.second].first != -1) {
        int q = 0;
		while (start.first != -2) {
			route.push_back({ start.first, start.second});
			start = trace[start.first][start.second];
		}
	}

    return route.size() >= 2 &&  route.size() <= 4;
}

bool checkLegalMove(headerList *board, int row, int col, int lvl){
    int _col, _row;
    if (lvl <= 3){
        _col = col;
        _row = row;
    }
    else {
        _col = row;
        _row = col;
    }
    vector<pair <int, int>> check[26];
    for (int i = 1; i <= _row; i++){
        for (int j = 1; j <= _col; j++){
            if (traceH(board, i) != nullptr && trace(traceH(board, i)->head, j) != nullptr)
            {
                if (trace(traceH(board, i)->head, j)->key != 0)
                    check[trace(traceH(board, i)->head, j)->key - (int)'A'].push_back(make_pair(i, j));
            }
            else
                break;
        }
    }

    for (int i = 0; i < 26; i++)
        if (!check[i].empty())
            for (int j = 0; j < check[i].size() - 1; j++)
                for (int _j = j + 1; _j < check[i].size(); _j++)
                {
                    if (findPath(board, _row, _col, check[i][j].first, check[i][_j].first, check[i][j].second, check[i][_j].second))
                    {
                        return true;
                    }
                }
    return false;
}
