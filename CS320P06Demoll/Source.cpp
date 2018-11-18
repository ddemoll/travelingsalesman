#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <cfloat>
using namespace std;

const bool _DEBUG_ = false;

//adjaceny matrix
vector<vector<double> > rows;
//optimal tour path tracker
vector<int> path;
//memoization table
//calls to g where s is the empty set are not memoized because they can be looked up in the adjaceny matrix
unordered_map<string, double> memos;

double g(int i, const vector<int> &s, bool q);
/*
Adds value of j to used to minimize function g to path
*/
void p(int i, vector<int> &s) {
	if (!s.empty()) {
		double min = DBL_MAX;
		int minj = 0;
		vector<int> minS;
		for (size_t k = 0; k < s.size(); ++k) {
			int j = s[k];
			vector<int> newS(s);
			newS.erase(find(newS.begin(), newS.end(), j));
			double cost = rows[i][j] + g(j, newS, false);
			if (cost <= min) {
				min = cost;
				minj = j;
				minS = newS;
			}


		}
		path.push_back(minj);
		p(minj, minS);
	}
	
}

/*
function g(i, S, firstCall) is defined as the length of the shortest path from vertex i to
vertex 1 and that passes through each vertex in S one and only one time
*/
double g(int i, const vector<int> &s, bool firstCall) {
	//generate unique key for memoization
	string args = to_string(i);
	for (size_t z = 0; z < s.size(); ++z)
		args += to_string(s[z]);
	
	//lookup function arguments in table
	unordered_map<string, double>::const_iterator memoized = memos.find(args);
	if (memoized != memos.end()) {
		if(_DEBUG_)
			cout << "memo " << args << endl;
		return memoized->second;
	}

	if (s.empty()) {
		if(_DEBUG_)
			cout << "g(" << i+1 << ", null) = " << rows[i][0] << endl;
		return rows[i][0];
	}
	double min = DBL_MAX;
	
	int minj = 0; //cheapest vertex to visit next
	vector<int> minS;
	//find min cost for all j in s
	for (size_t k = 0; k < s.size(); ++k) {
		int j = s[k];
		vector<int> newS(s);
		newS.erase(find(newS.begin(), newS.end(), j));
		double cost = rows[i][j] + g(j, newS, false);
		if (cost <= min) {
			min = cost;
			minj = j;
			minS = newS;
		}
		
			
	}
	if (firstCall) {
		//keep track of optimal path to report optimal cycle
		path.push_back(minj);
		p(minj, minS);
	}
	

	if (_DEBUG_) {
		cout << "g(" << i + 1 << ", {";
		for (size_t j = 0; j < s.size(); ++j)
			cout << s[j] + 1 << ", ";
		cout << "}) = " << min << endl;
	}
	
	//memoization
	memos[args] = min;

	return min;
}

int main() {
	//open file
	string fileInName;
	cout << "Enter the file name: ";
	cin >> fileInName;
	ifstream fileIn;
	fileIn.open(fileInName);
	if (!fileIn) {
		cerr << "Cannot open '" << fileInName << "'" << endl;
		exit(1);
	}
	
	//declare vertex id to string name dictionary
	unordered_map<int, string> vertexMap;
	
	//read file into adjacency matrix
	string line;
	int numVertices = 0;
	while (getline(fileIn, line)) {
		stringstream s(line);
		double ID, weight;
		vector<double> row;
		s >> ID;
		s >> vertexMap[numVertices++];
		int vertexID = 1;
		while (s >> ID) {
			int IDdiff = ID - vertexID;
			//mark with infinity if no edge exists
			if (IDdiff > 0) {
				for(int i=0; i<IDdiff; ++i)
					row.push_back(DBL_MAX);
				
			}
			vertexID += ID - vertexID+1;
			s >> weight;
			row.push_back(weight);
		
		}

		rows.push_back(row);
	}
	//backfill row with infinity if no edge exists
	for (int i = 0; i < rows.size(); ++i) {
		int length = rows[i].size();
		for (int j = 0; j < (numVertices - length); ++j)
			rows[i].push_back(DBL_MAX);
	}
	

	if (_DEBUG_) {
		cout << "Adjacency matrix: " << endl;
		for (int i = 0; i < rows.size(); ++i) {
			for (int j = 0; j < rows.size(); ++j)
				cout << rows[i][j] << " ";
			cout << endl;
		}
	}
	
	
	
	//generate first subset = V - {1}
	vector<int> v(numVertices-1);
	iota(v.begin(), v.end(), 1);
	//calculate optimal hamiltonian circuit
	double optimalCost = g(0, v, true);

	//output Optimal Tour Cost and corresponding path
	if (optimalCost != DBL_MAX) {
		cout << "Optimal Tour Cost = [" << optimalCost << ", <" << vertexMap[0] << ",";
		for (size_t j = 0; j < path.size(); ++j) {
			cout << vertexMap[path[j]];
			if (j != path.size() - 1) cout << ",";
		}
			
		cout << ">]" << endl;
	}
	else {
		cout << "No Hamiltonian circuit exists." << endl;
	}
	
	
	return 0;
}