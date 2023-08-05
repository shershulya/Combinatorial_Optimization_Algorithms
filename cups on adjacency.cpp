#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

int main(void) {
	int n, m;
	std::cin >> n >> m;
	// std::cout << n << " " << m << std::endl;
	std::vector<std::vector<long>> time(n, std::vector<long>(n, 1441));
	std::vector<std::vector<long>> weight(n, std::vector<long>(n, 0));
	
	long a, b;
	long time_cur, weight_cur;
	for (int i = 0; i < m; ++i) {
		std::cin >> a >> b;
		std::cin >> time_cur >> weight_cur;
		weight_cur = (weight_cur - 3000000) / 100;
		--a;
		--b;
		weight[a][b] = weight[b][a] = weight_cur;
		time[a][b] = time[b][a] = time_cur;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << std::setw(5) << weight[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "----------" << std::endl;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			std::cout << std::setw(5) << time[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "----------" << std::endl;

	std::vector<long> path_time(n, 1441);
	std::vector<long> cups(n, 0);
	path_time[0] = 0;
	cups[0] = 10000000;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			
			for (int k = 0; k < n; ++k) {
				std::cout << cups[k] << " ";
			}
			std::cout << std::endl;

			if (i == j)
				continue;
			long min = std::min(cups[j], weight[i][j]);
			long total_time = path_time[j] + time[i][j];
			if (cups[i] < min && total_time < 1441) {
				cups[i] = min;
				path_time[i] = total_time;
			}
		}
	}

	// for (int i = 0; i < n; ++i) {
	// 	std::cout << cups[i] << " ";
	// }
	// std::cout << std::endl;

	// for (int i = 0; i < n; ++i) {
	// 	std::cout << path_time[i] << " ";
	// }
	// std::cout << std::endl;

	std::cout << cups[n - 1] << std::endl;
	return 0;
}