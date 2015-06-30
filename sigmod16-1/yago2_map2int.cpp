#include "iostream"
#include "fstream"
#include "sstream"
#include "map"
#include "set"
#include "queue"
#include "time.h"

using namespace std;

int main(int argc, char *argv[]) {

	/**data sample: <id_jqyg1z_zkl_1xi58gi>	<Jefferson_County,_Texas>	<owns>	<Jack_Brooks_Regional_Airport>*/

	string filename = "./datademo/g1";
	string label_pattern;
	if (argc < 3) {
		cout << "para: graphfilename label_pattern" << endl;
		return -1;
	}
	filename = argv[1];
	label_pattern = argv[2];

	map<string, string> edgetype_subject;
	map<string, string>	edgetype_object;

	ifstream lfin(label_pattern.c_str());
	string line;
	string s1, s2, s3;
	while (getline(lfin, line)) {
		stringstream ss(line);
		ss >> s1 >> s2 >> s3;
		edgetype_subject.insert(pair<string, string>(s3, s1));
		edgetype_object.insert(pair<string, string>(s3, s2));
	}

	for (map<string, string>::iterator it = edgetype_object.begin(); it != edgetype_object.end(); it++) {
		cout << it->first << " -> " << it->second << endl;
	}
	for (map<string, string>::iterator it = edgetype_subject.begin(); it != edgetype_subject.end(); it++) {
		cout << it->first << " -> " << it->second << endl;
	}

	/**global graph*/
	map<string, int> vnum_map;
	map<int, string> vlabel_map;
	map<string, int> elabel_map;

	ifstream fin(filename.c_str());
	string item_id, item_subj, item_pred, item_obj;
	int vlabelindex = 0;
	int elabelindex = 0;

	int subj, pred, obj;
	ofstream fout("yago2_numeric.dat");

	int i = 0;

	while (getline(fin, line)) {
		if (i != 0) {
			stringstream ss(line);
			// cout<<line<<endl;
			ss >> item_id >> item_subj >> item_pred >> item_obj;
			if (vnum_map.find(item_subj) == vnum_map.end()) {
				vnum_map.insert(pair<string, int>(item_subj, vlabelindex++));
			}
			subj = vnum_map.at(item_subj);

			if (elabel_map.find(item_pred) == elabel_map.end()) {
				elabel_map.insert(pair<string, int>(item_pred, elabelindex++));
			}
			pred = elabel_map.at(item_pred);

			if (vnum_map.find(item_obj) == vnum_map.end()) {
				vnum_map.insert(pair<string, int>(item_obj, vlabelindex++));
			}
			obj = vnum_map.at(item_obj);
			fout << subj << "\t" << pred << "\t" << obj << endl;

			if (edgetype_subject.find(item_pred) != edgetype_subject.end()) {
				string sub_label = edgetype_subject.at(item_pred);
				if (sub_label != "-" && vlabel_map.find(subj) == vlabel_map.end()) {
					vlabel_map.insert(pair<int, string>(subj, sub_label));
				}
			}
			else {
				cout << "NO_EDGE_KEY??" << item_pred;
			}

			if (edgetype_subject.find(item_pred) != edgetype_subject.end()) {
				string obj_label = edgetype_object.at(item_pred);
				if (obj_label != "-" && vlabel_map.find(obj) == vlabel_map.end()) {
					vlabel_map.insert(pair<int, string>(obj, obj_label));
				}
			}
			else {
				cout << " ??" << item_pred << endl;
			}
		}
		i++;
	}
	fout.close();

	ofstream vmap_out("yago2_v.map");
	for (map<string, int>::iterator it = vnum_map.begin(); it != vnum_map.end(); it++) {
		if (vlabel_map.find(it->second) != vlabel_map.end()) {
			vmap_out << it->second << "\t" << it->first << "\t" << vlabel_map.at(it->second) << endl;
		}
		else {
			vmap_out << it->second << "\t" << it->first << "\tother" << endl;
		}

	}
	vmap_out.close();

	ofstream emap_out("yago2_e.map");
	for (map<string, int>::iterator it = elabel_map.begin(); it != elabel_map.end(); it++) {
		emap_out << it->second << "\t" << it->first << endl;
	}
	emap_out.close();

	cout << "finished. with vlabel_kind = " << vlabelindex << ", elabel_kind = " << elabelindex << endl;
}