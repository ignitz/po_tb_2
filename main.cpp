#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>
#include <map>

// class Graph {
// private:
//
// public:
//
// };

using graph = std::vector<std::vector<char>>;

void init_jobs(std::unordered_map<std::string, size_t>& jobs);
void init_time(std::vector<double>& time, const std::unordered_map<std::string, size_t>& jobs);
void init_graph(graph& g, const std::unordered_map<std::string, size_t>& jobs);

void heuro_doidao(std::vector<double>&, graph&);

void bruteforce(std::vector<double>& time, graph& g);

int main() {
	std::unordered_map<std::string, size_t> jobs;
	init_jobs(jobs);
	//for(auto& it: jobs) std::cout<<it.first<<' '<<it.second<<'\n';

	std::vector<double> time(jobs.size());
	init_time(time, jobs);
	//for(auto& it: time) std::cout<<it<<'\n';

	graph g(jobs.size());
	init_graph(g, jobs);

    std::cout << "/* message */" << std::endl;
    //bruteforce(time, g);
    heuro_doidao(time, g);
}

void heuro_doidao(std::vector<double>& time, graph& g) {

    std::map<int, size_t> degree;
    for (size_t i = 0; i < g.size(); i++) {
        int x=0;
        for (size_t j = 0; j < g[i].size() ; j++) {
            if(j == i) continue;
            x += !g[i][j];
        }
        degree[i] = x;
        //std::cout << degree[i] << '\n';
    }

    while (!degree.empty()) {
        auto last = degree.erase(--degree.end());
        size_t vertex = last->second;
        for(auto it = degree.begin(); it != degree.end(); ++it) {
            if (it->second == vertex) {

            }
        }
    }



}

/*
void bruteforce(std::vector<double>& time, graph& g){
	std::vector<size_t> pos(time.size());
	std::vector<double> init_time(time.size());
	for(size_t i=0; i<pos.size(); ++i) pos[i]=i;

	do {
		for(size_t i=0; i<pos.size(); ++i) std::cout<<pos[i]<<' ';
	std::cout<<'\n';

	} while (std::next_permutation(pos.begin(), pos.end()));
}
*/
void init_jobs(std::unordered_map<std::string, size_t>& jobs) {
	std::string buf;
	//set JOBS :=
	std::cin >> buf >> buf >> buf;
	size_t i = 0;
	bool cont = true;
	while (std::cin >> buf, buf != ";") {
		if (buf.back() == ';') {
			buf.erase(buf.end()-1);
			cont = false;
		}
		jobs[buf] = i;
		++i;
		if(!cont) break;
	}
}

void init_time(std::vector<double>& time, const std::unordered_map<std::string, size_t>& jobs){
	std::string buf;
	//param TIME :=
	std::cin >> buf >> buf >> buf;
	double t;
	while (std::cin >> buf) {
		if ( buf == ";") break;
		std::cin >> t;
		size_t place = jobs.at(buf);
		assert(place < time.size());
		time[place] = t;
	}
}

void init_graph(graph& g, const std::unordered_map<std::string, size_t>& jobs){
	std::string buf, buf2;
	for (auto& it: g) it.resize(jobs.size());

	//set INCOMP :=
	std::cin >> buf >> buf >> buf;
	bool cont = true;
	while (std::cin >> buf >> buf2, buf != ";") {
		if (buf2.back() == ';') {
			buf2.erase(buf2.end()-1);
			cont = false;
		}
		if (buf2.back() == ',') buf2.erase(buf2.end()-1);

		size_t i = jobs.at(buf), j = jobs.at(buf2);
		g[i][j] = 1;
		g[j][i] = 1;
		if(!cont) break;
	}
}
