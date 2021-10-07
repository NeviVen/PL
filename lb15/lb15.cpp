#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>


using namespace std;

void output_state(stack<int> st, const string& input)
{
	cout << "\nInput string -> " << input << endl;

	cout << "Stack -> ";
	int size_of_stack = st.size();
	for (int i = 0; i < size_of_stack; ++i)
	{
		cout << st.top() << ((i == size_of_stack - 1) ? " " : ", ");
		st.pop();
	}
	cout << endl << endl;

}

int main() {

	vector<char> terms{ '+', '-', '*', '/', '(', ')', 'i', 'n', '$' };
	vector<char> not_terms{ 'E', 'T', 'F' };
	vector<string> rules{ "E'->E", "E->E+T", "E->E-T", "E->T", "T->T*F", "T->T/F", "T->F", "F->(E)", "F->i", "F->n" };
	

	vector<vector<string>> action_table{
		{ "err", "err", "err", "err", "s4", "err", "s5", "s6", "err"},
		{ "s7", "s8", "err", "err", "err", "err", "err", "err", "acc" },
		{ "r3", "r3", "s9", "s10", "err", "r3", "err", "err", "r3" },
		{ "r6", "r6", "r6", "r6", "err", "r6", "err", "err", "r6" },
		{ "err", "err", "err", "err", "s4", "err", "s5", "s6", "err" },
		{ "r8", "r8", "r8", "r8", "err", "r8", "err", "err", "r8" },
		{ "r9", "r9", "r9", "r9", "err", "r9", "err", "err", "r9" },
		{ "err", "err", "err", "err", "s4", "err", "s5", "s6", "err" },
		{ "err", "err", "err", "err", "s4", "err", "s5", "s6", "err" },
		{ "err", "err", "err", "err", "s4", "err", "s5", "s6", "err" },
		{ "err", "err", "err", "err", "s4", "err", "s5", "s6", "err" },
		{ "s7", "s8", "err", "err", "err", "s16", "err", "err", "err" },
		{ "r1", "r1", "s9", "s10", "err", "r1", "err", "err", "r1" },
		{ "r2", "r2", "s9", "s10", "err", "r2", "err", "err", "r2" },
		{ "r4", "r4", "r4", "r4", "err", "r4", "err", "err", "r4" },
		{ "r5", "r5", "r5", "r5", "err", "r5", "err", "err", "r5" },
		{ "r7", "r7", "r7", "r7", "err", "r7", "err", "err", "r7" }
	};

	vector<vector<int>> goto_table{
		{1, 2, 3},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{11, 2, 3},
		{0, 0, 0},
		{0, 0, 0},
		{0, 12, 3},
		{0, 13, 3},
		{0, 0, 14},
		{0, 0, 15},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};

	stack<int> st;
	st.push(0);

	string input;
	cout << "Input string: ";
	getline(cin, input);
	input.push_back('$');

	for (auto ch : input)
	{
		if (find(terms.begin(), terms.end(), ch) == terms.end())
		{
			cerr << "Invalid input\n";
			return 1;
		}
	}

	while (true)
	{
		int row_act = st.top();
		int col_act = distance(terms.begin(), find(terms.begin(), terms.end(), input[0]));

		string table_rule = action_table[row_act][col_act];

		if (table_rule[0] == 's')
		{
			st.push(stoi(table_rule.erase(0, 1)));
			input.erase(0, 1);

			output_state(st, input);
		}
		else if (table_rule[0] == 'r')
		{
			string rule = rules[stoi(table_rule.erase(0, 1))];

			for (int i = 0; i < rule.length() - 3; ++i)
				st.pop();

			int row_goto = st.top();
			int col_goto = distance(not_terms.begin(), find(not_terms.begin(), not_terms.end(), rule[0]));

			st.push(goto_table[row_goto][col_goto]);

			output_state(st, input);
		}
		else if (table_rule == "acc")
		{
			cout << "Input belongs to grammar\n";
			break;
		}
		else if (table_rule == "err")
		{
			cerr << "Input doesn\'t belong to grammar\n";
			return 0;
		}
		else
		{
			cerr << "Unidentified ERROR\n";
			return 1;
		}
	}
}
