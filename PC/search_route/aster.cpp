#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <utility>

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
        if (line == "decoy") {
            grid[y][x] = 1;
        }
        else if (line == "treasure") {
            grid[y][x] = 2;
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

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (grid[i][j] == 2) {
                grid[i][j] = 0;
            }
        }
    }

    //新しいファイルを作成して開く
    std::ofstream outputFile("keiro.txt");

    // ファイルが正常に開けたかを確認
    if (!outputFile.is_open()) {
        std::cerr << "ファイルを作成・開けませんでした" << std::endl;
        return 1;
    }



    //Aスターアルゴリズム
    //スタート(3,0)→トレジャーブロックまで
    int startX = 0;
    int startY = 3;
    int goalX = gx;
    int goalY = gy;

    AStar astar(grid, startX, startY, goalX, goalY);
    std::vector<std::pair<int, int>> path = astar.findPath();

    int a = 0;
    //走交代の向き
    //↑：0
    //→：1
    //↓：2
    //←：3
    int direction = 1;

    //走交代の移動
    //int wark;

    std::vector<std::pair<int, int>> p = {
            std::make_pair(0,3),
    };

    //添え字用変数
    int tmp = 0;

    if (!path.empty()) {
        //走行体の座標
        int curentXX = 0;
        int curentYY = 3;


        /*int cux = 0;
        int cuy = 3;*/
        std::cout << "Path found:" << std::endl;
        //std::cout << curentYY << curentXX << std::endl;
        
        for (const auto& point : path) {
            /*if (a == 0) {
                a++;
                continue;
            }*/
            std::cout << "(" << point.second << ", " << point.first << ")" << std::endl;
            if (point.second == (p[tmp].second - 1) && point.first == p[tmp].first && direction == 0) {
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 0 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second - 1) && point.first == p[tmp].first && direction == 1) {
                direction = 0;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second - 1) && point.first == p[tmp].first && direction == 2) {
                direction = 0;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second - 1) && point.first == p[tmp].first && direction == 3) {
                direction = 0;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second) && point.first == (p[tmp].first + 1) && direction == 0) {
                direction = 1;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second) && point.first == (p[tmp].first + 1) && direction == 1) {
                direction = 1;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 0 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second) && point.first == (p[tmp].first + 1) && direction == 2) {
                direction = 1;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second) && point.first == (p[tmp].first + 1) && direction == 3) {
                direction = 1;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second + 1) && point.first == p[tmp].first && direction == 0) {
                direction = 2;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second + 1) && point.first == p[tmp].first && direction == 1) {
                direction = 2;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second + 1) && point.first == p[tmp].first && direction == 2) {
                direction = 2;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 0 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second + 1) && point.first == p[tmp].first && direction == 3) {
                direction = 2;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == p[tmp].second && point.first == (p[tmp].first - 1) && direction == 0) {
                direction = 3;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == p[tmp].second && point.first == (p[tmp].first - 1) && direction == 1) {
                direction = 3;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == p[tmp].second && point.first == (p[tmp].first - 1) && direction == 2) {
                direction = 3;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }

            else if (point.second == p[tmp].second && point.first == (p[tmp].first - 1) && direction == 3) {
                direction = 3;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 0 << std::endl;
                outputFile << 0 << std::endl;
            }
            else {
                //std::cout << "(" << curentYY << ", " << curentXX << ")" << std::endl;
                std::cout << "ない"<< std::endl;
                // std::cout << p.first << std::endl;
                // printf("%d,%d\n", curentYY, curentXX);
            }
            // std::cout << p.first << std::endl;
             //std::cout << p.first << std::endl;
             //std::cout << point.first << std::endl;
             //p.first = point.first;
             //std::cout << p.first << std::endl;
        }
    }
    else {
        std::cout << "No path found." << std::endl;
    }


    if (!outputFile.is_open()) {
        std::cerr << "ファイルを作成・開けませんでした" << std::endl;
        return 1;
    }

    //トレジャーブロック→ゴール(3,3)まで
    int startX2 = gx;
    int startY2 = gy;
    int goalX2 = 3;
    int goalY2 = 3;

    AStar tore(grid, startX2, startY2, goalX2, goalY2);
    std::vector<std::pair<int, int>> path2 = tore.findPath();

    //最初はcontinueする
    a = 0;

    if (!path2.empty()) {
        std::cout << "Path found:" << std::endl;
        for (const auto& point : path2) {
            if (a == 0) {
                a++;
                continue;
            }
            std::cout << "(" << point.second << ", " << point.first << ")" << std::endl;
            if (point.second == (p[tmp].second - 1) && point.first == p[tmp].first && direction == 0) {
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 0 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second - 1) && point.first == p[tmp].first && direction == 1) {
                direction = 0;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second - 1) && point.first == p[tmp].first && direction == 2) {
                direction = 0;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second - 1) && point.first == p[tmp].first && direction == 3) {
                direction = 0;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second) && point.first == (p[tmp].first + 1) && direction == 0) {
                direction = 1;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second) && point.first == (p[tmp].first + 1) && direction == 1) {
                direction = 1;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 0 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second) && point.first == (p[tmp].first + 1) && direction == 2) {
                direction = 1;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second) && point.first == (p[tmp].first + 1) && direction == 3) {
                direction = 1;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second + 1) && point.first == p[tmp].first && direction == 0) {
                direction = 2;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second + 1) && point.first == p[tmp].first && direction == 1) {
                direction = 2;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second + 1) && point.first == p[tmp].first && direction == 2) {
                direction = 2;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 0 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == (p[tmp].second + 1) && point.first == p[tmp].first && direction == 3) {
                direction = 2;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == p[tmp].second && point.first == (p[tmp].first - 1) && direction == 0) {
                direction = 3;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == p[tmp].second && point.first == (p[tmp].first - 1) && direction == 1) {
                direction = 3;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 2 << std::endl;
                std::cout << 2 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 2 << std::endl;
                outputFile << 0 << std::endl;
            }
            else if (point.second == p[tmp].second && point.first == (p[tmp].first - 1) && direction == 2) {
                direction = 3;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 1 << std::endl;
                std::cout << 0 << std::endl;
                outputFile << 1 << std::endl;
                outputFile << 0 << std::endl;
            }

            else if (point.second == p[tmp].second && point.first == (p[tmp].first - 1) && direction == 3) {
                direction = 3;
                p.push_back(std::make_pair(point.first, point.second));
                tmp++;

                std::cout << 0 << std::endl;
                outputFile << 0 << std::endl;
            }
            else {
                //std::cout << "(" << curentYY << ", " << curentXX << ")" << std::endl;
                std::cout << "ない" << std::endl;
                // std::cout << p.first << std::endl;
                // printf("%d,%d\n", curentYY, curentXX);
            }

            if (point.second == 1 & point.first == 3 & direction  ==0 ) {
                outputFile << 1 << std::endl;
                std::cout << 1 << std::endl;
            }
            else if (point.second == 1 & point.first == 3 & direction == 2) {
                outputFile << 2 << std::endl;
                std::cout << 2 << std::endl;
            }
            else if (point.second == 1 & point.first == 3 & direction == 3) {
                outputFile << 1 << std::endl;
                outputFile << 1 << std::endl;
                std::cout << 1 << std::endl;
                std::cout << 1 << std::endl;
            }
            else if (point.second == 2 & point.first == 3 & direction == 0) {
                outputFile << 1 << std::endl;
                std::cout << 1 << std::endl;
            }
            else if (point.second == 2 & point.first == 3 & direction == 2) {
                outputFile << 2 << std::endl;
                std::cout << 2 << std::endl;
            }
            else if (point.second == 2 & point.first == 3 & direction == 3) {
                outputFile << 1 << std::endl;
                outputFile << 1 << std::endl;
                std::cout << 1 << std::endl;
                std::cout << 1 << std::endl;

            }
            else if (point.second == 3 & point.first == 3 & direction == 0) {
                outputFile << 1 << std::endl;
                std::cout << 1 << std::endl;
            }
            else if (point.second == 3 & point.first == 3 & direction == 2) {
                outputFile << 2 << std::endl;
                std::cout << 2 << std::endl;
            }
            else if (point.second == 3 & point.first == 3 & direction == 3) {
                outputFile << 1 << std::endl;
                outputFile << 1 << std::endl;
                std::cout << 1 << std::endl;
                std::cout << 1 << std::endl;
            }
        }
    }
    else {
        std::cout << "No path found." << std::endl;
    }


    //ファイルを閉じる
    outputFile.close();



    return 0;
}