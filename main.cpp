#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>
#include <set>

using time_type = double;
// O ideal seria ser utilizado um BITSET ao inves do SET, mas
// na biblioteca padrao do c++ nao tem
using graph = std::vector<std::set<size_t>>;

void init_jobs(std::unordered_map<std::string, size_t>& job_id,
		std::unordered_map<size_t, std::string>& id_job);
void init_time(std::vector<time_type>& time, const std::unordered_map<std::string, size_t>& job_id);
void init_graph(graph& g, const std::unordered_map<std::string, size_t>& job_id);

void bruteforce(std::vector<time_type>& time, graph& g);
void heuristic(std::vector<time_type>& time, graph& g, std::vector<std::pair<size_t, time_type>>& answer);


int main(int argc, char **argv) {
	std::unordered_map<std::string, size_t> job_id;
	std::unordered_map<size_t, std::string> id_job;
	init_jobs(job_id, id_job);
	//for(auto& it: job_id) std::cout<<it.first<<' '<<it.second<<std::endl;

	std::vector<time_type> time(job_id.size());
	init_time(time, job_id);
	//for(auto& it: time) std::cout<<it<<'\n';
	//std::cout<<"aqui"<<std::endl;
	graph g(job_id.size());
	init_graph(g, job_id);

	std::vector<std::pair<size_t, time_type>> answer;
	heuristic(time, g, answer);
	for (auto& it: answer) std::cout << id_job[it.first]<<' '<<it.second<<'\n';
	//std::cout<<answer.back().second+time[answer.back().first]<<'\n';
}

bool overlap(std::set<size_t> setA, std::set<size_t> setB) {
	auto it1 = setA.begin();
	auto it2 = setB.begin();
	if (it1 == setA.end() || it2 == setB.end()) return false;
	while (true) {
		while (*it1 < *it2) {
			++it1;
			if (it1 == setA.end()) return false;
		}
		if (*it1 == *it2) return true;
		++it2;
		if (it2 == setB.end()) return false;
	}
	return false;
}

void heuristic(std::vector<time_type>& time, graph& g, std::vector<std::pair<size_t, time_type>>& answer){
	std::set<size_t> to_execute;
	for(size_t i=0; i<time.size(); ++i) to_execute.insert(i);
	std::multimap<time_type, size_t> executing_time;
	std::set<size_t> executing;
	time_type current_time = 0;

	while (!to_execute.empty()) {
		std::multimap<int, size_t> degree;
		for (auto& it: to_execute) {
			degree.insert(std::make_pair(g[it].size(), it));
		}
		for (auto& it: degree) {
			//vai pegando o cara com menos dependencias e que pode executar
			size_t A = it.second;
			if (!overlap(executing, g[A])) {
				to_execute.erase(to_execute.find(A));
				executing_time.insert(std::make_pair(current_time+time[A], A));
				executing.insert(A);
			}
		}
		//tira o primeiro a acabar de executar. outros podem acabar ao mesmo tempo
		std::pair<time_type, size_t> exit_pair = *(executing_time.begin());
		current_time = exit_pair.first;
		while (current_time >= exit_pair.first) {
			executing_time.erase(executing_time.begin());
			executing.erase(executing.find(exit_pair.second));
			for (auto& it: g) it.insert(exit_pair.second);
			answer.push_back(std::make_pair(exit_pair.second, exit_pair.first));
			if(executing_time.empty()) break;
			exit_pair = *(executing_time.begin());
		}
	}
	//esvazia a fila dos executando
	while (!executing_time.empty()) {
		auto exit_pair = *(executing_time.begin());
		executing_time.erase(executing_time.begin());
		executing.erase(executing.begin());
		current_time = exit_pair.first;
		for (auto& it: g) it.insert(exit_pair.second);
		answer.push_back(std::make_pair(exit_pair.second, exit_pair.first));
	}
}

void init_jobs(std::unordered_map<std::string, size_t>& job_id,
		std::unordered_map<size_t, std::string>& id_job) {
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
		if (buf.back() == ',') buf.erase(buf.end()-1);
		job_id[buf] = i;
		id_job[i] = buf;
		++i;
		if(!cont) break;
	}
}

void init_time(std::vector<time_type>& time, const std::unordered_map<std::string, size_t>& job_id){
	std::string buf;
	//param TIME :=
	std::cin >> buf >> buf >> buf;
	time_type t;
	while (std::cin >> buf) {
		if ( buf == ";") break;
		std::cin >> t;
		size_t place = job_id.at(buf);
		assert(place < time.size());
		time[place] = t;
	}
}

void init_graph(graph& g, const std::unordered_map<std::string, size_t>& job_id){
	std::string buf, buf2;

	//set INCOMP :=
	std::cin >> buf >> buf >> buf;
	bool cont = true;
	while (std::cin >> buf >> buf2, buf != ";") {
		if (buf2.back() == ';') {
			buf2.erase(buf2.end()-1);
			cont = false;
		}
		if (buf2.back() == ',') buf2.erase(buf2.end()-1);

		size_t i = job_id.at(buf), j = job_id.at(buf2);
		g[i].insert(j);
		g[j].insert(i);
		if(!cont) break;
	}
}
