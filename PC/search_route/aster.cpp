#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cmath>
#include <vector>
#include <unordered_map>

class Node {
public:
    int x, y;
    int cost;
    int heuristic;

    Node(int x, int y) : x(x), y(y), cost(0), heuristic(0) {}

    int getTotalCost() const {
        return cost + heuristic;
    }
};

struct CompareNodes {
    bool operator()(const Node& a, const Node& b) {
        return a.getTotalCost() > b.getTotalCost();
    }
};

class AStar {
public:
    AStar(std::vector<std::vector<int>>& grid, int startX, int startY, int goalX, int goalY);
    std::vector<std::pair<int, int>> findPath();

private:
    std::vector<std::vector<int>> grid;
    int startX, startY, goalX, goalY;
    std::priority_queue<Node, std::vector<Node>, CompareNodes> openSet;
    std::unordered_map<int, int> cameFrom;
    std::unordered_map<int, int> gScores;
    std::unordered_map<int, int> hScores;
    int gridSize;
};

AStar::AStar(std::vector<std::vector<int>>& grid, int startX, int startY, int goalX, int goalY)
    : grid(grid), startX(startX), startY(startY), goalX(goalX), goalY(goalY), gridSize(grid.size()) {}

std::vector<std::pair<int, int>> AStar::findPath() {
    int startHash = startY * gridSize + startX;
    int goalHash = goalY * gridSize + goalX;

    openSet.push(Node(startX, startY));
    gScores[startHash] = 0;
    hScores[startHash] = std::abs(goalX - startX) + std::abs(goalY - startY);

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.x == goalX && current.y == goalY) {
            std::vector<std::pair<int, int>> path;
            int currentHash = goalHash;
            while (currentHash != startHash) {
                int x = currentHash % gridSize;
                int y = currentHash / gridSize;
                path.push_back(std::make_pair(x, y));
                currentHash = cameFrom[currentHash];
            }
            path.push_back(std::make_pair(startX, startY));
            std::reverse(path.begin(), path.end());
            return path;
        }

        int neighborsX[] = { 0, 0, 1, -1 };
        int neighborsY[] = { 1, -1, 0, 0 };

        for (int i = 0; i < 4; ++i) {
            int newX = current.x + neighborsX[i];
            int newY = current.y + neighborsY[i];

            if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridSize && grid[newY][newX] == 0) {
                int neighborHash = newY * gridSize + newX;
                int tentativeGScore = gScores[current.x + current.y * gridSize] + 1;

                if (gScores.find(neighborHash) == gScores.end() || tentativeGScore < gScores[neighborHash]) {
                    cameFrom[neighborHash] = current.x + current.y * gridSize;
                    gScores[neighborHash] = tentativeGScore;
                    hScores[neighborHash] = std::abs(goalX - newX) + std::abs(goalY - newY);
                    openSet.push(Node(newX, newY));
                }
            }
        }
    }

    return std::vector<std::pair<int, int>>();
}

int main() {
	//4*4の配列を定義して0で初期化
	//0：空
	//1：decoy
	//2：treasure
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };


	//座標の定義
	int x = 0;
	int y = 0;

    //ゴール座標の定義
    int gx = 0;
    int gy = 0;

	//ファイルを開く
	std::ifstream inputFile("treasureBlockData.txt");

	//ファイルが正常に開けたか確認
	if (!inputFile.is_open()) {
		std::cerr << "ファイルが開けませんでした" << std::endl;
		return 1;
	}

	//ファイルからデータの読み込み
	std::string line;
	while (std::getline(inputFile, line)) {
		if (line=="decoy") {
			grid[y][x] = 1;
		}
		else if (line == "treasure") {
            gx = x;
            gy = y;
		}
		std::cout << line << std::endl;
		if (x != 3) {
			x++;
		}
		else {
			x = 0;
			y++;
		}
	}

    //ファイルを閉じる
    inputFile.close();

	//マスの表示
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%2d", grid[i][j]);
		}
		printf("\n");
	}

	//Aスターアルゴリズム
    int startX = 0;
    int startY = 3;
    int goalX = gx;
    int goalY = gy;
    
    AStar astar(grid, startX, startY, goalX, goalY);
    std::vector<std::pair<int, int>> path = astar.findPath();

    if (!path.empty()) {
        std::cout << "Path found:" << std::endl;
        for (const auto& point : path) {
            std::cout << "(" << point.second << ", " << point.first << ")" << std::endl;
        }
    }
    else {
        std::cout << "No path found." << std::endl;
    }

    //新しいファイルを作成して開く
    std::ofstream outputFile("keiro.txt");

    // ファイルが正常に開けたかを確認
    if (!outputFile.is_open()) {
        std::cerr << "ファイルを作成・開けませんでした" << std::endl;
        return 1;
    }

    // ファイルにデータを書き込む
    for (const auto& point : path) {
        outputFile << "(" << point.second << ", " << point.first << ")" << std::endl;
        //std::cout << "(" << point.second << ", " << point.first << ")" << std::endl;
    }
    //outputFile << "これは新しいファイルに書き込まれたデータです。\n";
    //outputFile << "別の行にもデータを書き込むことができます。\n";

    // ファイルを閉じる
    outputFile.close();

	return 0;
}	