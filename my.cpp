#include <iostream>
#include <vector>

using namespace std;

bool one(vector<int>& nums) {
    for (size_t i = 0; i < nums.size(); i++) {
        for (size_t j = i + 1; j < nums.size(); j++) {
            if (nums[i] == nums[j]) {
                return true;
            }
        }
    }
    return false;
}

int missingNumberXOR(vector<int>& nums, int n) {
    int result = n;

    for (int i = 0; i < n; i++) {
        result ^= i;
        result ^= nums[i];
    }

    return result;
}

void testMissingNumberXOR() {
    vector<int> nums = {0, 1, 3, 4, 5};
    int n = nums.size();
    cout << "Mis : "<< missingNumberXOR(nums, n) << endl;
}


vector<int> findDisappearedNumbersMarking(vector<int>& nums, int n) {
    for (int i = 0; i < n; i++) {
        int index = abs(nums[i]) - 1;
        if (nums[index] > 0) {
            nums[index] = -nums[index];
        }
    }

    vector<int> result;
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) {
            result.push_back(i + 1);
        }
    }

    return result;
}

void testFindDisappearedNumbersMarking() {
    vector<int> nums = {4, 3, 2, 7, 8, 2, 3, 1};
    int n = nums.size();
    vector<int> result = findDisappearedNumbersMarking(nums, n);

    cout << "Disappeared Numbers (Marking): ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
}

vector<int> findTwoSumBruteForce(vector<int>& nums, int n, int target) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

void testFindTwoSumBruteForce() {
    vector<int> nums = {3, 7, 1, 5, 9};
    int target = 8;
    int n = nums.size();
    vector<int> result = findTwoSumBruteForce(nums, n, target);

    cout << "Two Sum (Brute Force): " << result[0] << ", " << result[1] << endl;
}

vector<int> countSmallerBruteForce(vector<int>& nums, int n) {
    vector<int> result(n, 0);

    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (nums[j] < nums[i]) {
                count++;
            }
        }
        result[i] = count;
    }

    return result;
}

void testCountSmallerBruteForce() {
    vector<int> nums = {6, 2, 5, 8, 3};
    int n = nums.size();
    vector<int> result = countSmallerBruteForce(nums, n);

    cout << "Smaller Count (Brute Force): ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
}

int minTimeDirect(vector<vector<int>>& points, int n) {
    int time = 0;
    
    for (int i = 1; i < n; i++) {
        int dx = points[i][0] - points[i - 1][0];
        int dy = points[i][1] - points[i - 1][1];

        if (dx < 0) dx = -dx;
        if (dy < 0) dy = -dy;

        time += (dx > dy) ? dx : dy;
    }

    return time;
}

void testMinTimeDirect() {
    vector<vector<int>> points = {{1, 2}, {3, 4}, {6, 8}, {9, 9}};
    int n = points.size();
    cout << "Min Time (Direct Distance): " << minTimeDirect(points, n) << endl;
}

vector<vector<int>> generateSpiralDirectional(int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    int left = 0, right = n - 1, top = 0, bottom = n - 1, num = 1;

    while (left <= right && top <= bottom) {
        for (int i = left; i <= right; i++) matrix[top][i] = num++;
        top++;
        for (int i = top; i <= bottom; i++) matrix[i][right] = num++;
        right--;
        for (int i = right; i >= left; i--) matrix[bottom][i] = num++;
        bottom--;
        for (int i = bottom; i >= top; i--) matrix[i][left] = num++;
        left++;
    }

    return matrix;
}

void testGenerateSpiralDirectional() {
    int n = 4;
    vector<vector<int>> matrix = generateSpiralDirectional(n);

    cout << "Here comes the fantastic spiral matrix with style:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "[" << matrix[i][j] << "] ";
        }
        cout << endl;
    }
}

void markIsland(vector<vector<char>>& grid, int r, int c, int rows, int cols) {
    vector<pair<int, int>> stack;
    stack.push_back({r, c});

    while (!stack.empty()) {
        auto [x, y] = stack.back();
        stack.pop_back();

        if (x < 0 || y < 0 || x >= rows || y >= cols || grid[x][y] == '0') continue;

        grid[x][y] = '0';

        stack.push_back({x + 1, y});
        stack.push_back({x - 1, y});
        stack.push_back({x, y + 1});
        stack.push_back({x, y - 1});
    }
}

int countIslandsIterative(vector<vector<char>>& grid, int rows, int cols) {
    int count = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '1') {
                count++;
                markIsland(grid, r, c, rows, cols);
            }
        }
    }
    return count;
}

void testCountIslandsIterative() {
    vector<vector<char>> grid = {
        {'1', '0', '1', '0', '0'},
        {'0', '1', '0', '0', '1'},
        {'1', '0', '1', '1', '1'},
        {'0', '0', '0', '1', '0'}
    };
    int rows = grid.size();
    int cols = grid[0].size();
    int result = countIslandsIterative(grid, rows, cols);

    cout << "Islands Identified (Loop-based): Our satellite scan detected " << result << " isolated landmasses!" << endl;
}

int maxProfitOnePass(vector<int>& prices, int n) {
    int minPrice = prices[0];
    int maxProfit = 0;

    for (int i = 1; i < n; i++) {
        if (prices[i] < minPrice) {
            minPrice = prices[i];
        } else {
            int profit = prices[i] - minPrice;
            if (profit > maxProfit) {
                maxProfit = profit;
            }
        }
    }

    return maxProfit;
}

void testMaxProfitOnePass() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    int n = prices.size();
    int result = maxProfitOnePass(prices, n);

    cout << " Smart Investor Alert! Maximum profit you could earn is: $" << result << " " << endl;
}

vector<int> sortedSquaresSorting(vector<int>& nums, int n) {
    vector<int> result(n);

    for (int i = 0; i < n; i++) {
        result[i] = nums[i] * nums[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (result[i] > result[j]) {
                int temp = result[i];
                result[i] = result[j];
                result[j] = temp;
            }
        }
    }

    return result;
}

void testSortedSquaresSorting() {
    vector<int> nums = {-6, -2, 0, 1, 5};
    int n = nums.size();
    vector<int> result = sortedSquaresSorting(nums, n);

    cout << " After applying the power of squares, behold the new sequence: " << endl;
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
}

vector<vector<int>> threeSumTwoPointer(vector<int>& nums, int n) {
    vector<vector<int>> result;
    
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    result.push_back({nums[i], nums[j], nums[k]});
                }
            }
        }
    }
    
    return result;
}

void testThreeSumTwoPointer() {
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    int n = nums.size();
    vector<vector<int>> result = threeSumTwoPointer(nums, n);

    cout << " Found the magical triplets summing to zero: " << endl;
    for (auto triplet : result) {
        cout << "[" << triplet[0] << ", " << triplet[1] << ", " << triplet[2] << "]" << endl;
    }
}

vector<vector<int>> threeSumBruteForce(vector<int>& nums, int n) {
    vector<vector<int>> result;

    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 1; j < n - 1; j++) {
            for (int k = j + 1; k < n; k++) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    result.push_back({nums[i], nums[j], nums[k]});
                }
            }
        }
    }

    return result;
}

void testThreeSumBruteForce() {
    vector<int> nums = {-3, 1, 2, -1, -2, 0, 3};
    int n = nums.size();
    vector<vector<int>> result = threeSumBruteForce(nums, n);

    cout << " Alert! Triplets achieving zero sum detected! " << endl;
    for (auto triplet : result) {
        cout << "Triplet -> " << triplet[0] << ", " << triplet[1] << ", " << triplet[2] << endl;
    }
}

int longestMountainTwoPointer(vector<int>& arr, int n) {
    int longest = 0;

    for (int i = 1; i < n - 1; i++) {
        if (arr[i] > arr[i - 1] && arr[i] > arr[i + 1]) {
            int left = i - 1, right = i + 1;

            while (left > 0 && arr[left] > arr[left - 1]) {
                left--;
            }

            while (right < n - 1 && arr[right] > arr[right + 1]) {
                right++;
            }

            int length = right - left + 1;
            if (length > longest) {
                longest = length;
            }
        }
    }

    return longest;
}

void testLongestMountainTwoPointer() {
    vector<int> arr = {2, 1, 4, 7, 3, 2, 5};
    int n = arr.size();
    int result = longestMountainTwoPointer(arr, n);

    cout << "️ The tallest and longest mountain found spans " << result << " units! ️" << endl;
}


int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 1};
    cout << (one(nums) ? "true" : "false") << endl;

    testMissingNumberXOR();

    testFindDisappearedNumbersMarking();

    testFindTwoSumBruteForce();

    testCountSmallerBruteForce();

    testMinTimeDirect();

    testGenerateSpiralDirectional();

    testCountIslandsIterative();

    testMaxProfitOnePass();

    testSortedSquaresSorting();

    testThreeSumTwoPointer();

    testThreeSumBruteForce();

    testLongestMountainTwoPointer();








    return 0;
}
