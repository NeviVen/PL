#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void output_state(stack<char> st, const string& input)
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

int main()
{
	/*
	Grammar:
		E->TU
		U->+TU
			|-TU
			|eps
		T->FQ
		Q->*FQ
			|/FQ
			|eps
		F->i
			|n
			|(E)
	*/
	vector<char> notTerms{ 'E', 'U', 'T', 'Q', 'F' };
	vector<char> terms{ 'i', 'n', ')', '(', '$', '+', '-', '*', '/' };
	vector<vector<string>> ll_table{ {"TU", "TU", "-1", "TU", "-1", "-1", "-1", "-1", "-1"},
									 {"-1", "-1", "", "-1", "", "+TU", "-TU", "-1", "-1"},
									 {"FQ", "FQ", "-1", "FQ", "-1", "-1", "-1", "-1", "-1"},
									 {"-1", "-1", "", "-1", "", "", "", "*FQ", "/FQ"},
									 {"i", "n", "-1", "(E)", "-1", "-1", "-1", "-1", "-1"} };

	string input;
	cout << "Input string: ";
	getline(cin, input);
	input.push_back('$');

	//check is input valid
	for (auto ch : input)
	{
		if (find(terms.begin(), terms.end(), ch) == terms.end())
		{
			cerr << "Input string is invalid\n";
			return 1;
		}
	}

	stack<char> st;
	st.push('$');
	st.push('E');


	while (!(input.empty()))
	{
		//if at the top of the stack term
		if (input[0] == st.top())
		{
			st.pop();
			input.erase(0, 1);

			output_state(st, input);

		}
		//if at the top of the stack notTerm
		else if (input[0] != st.top() && find(notTerms.begin(), notTerms.end(), st.top()) != notTerms.end())
		{
			int col = distance(terms.begin(), find(terms.begin(), terms.end(), input[0]));
			int row = distance(notTerms.begin(), find(notTerms.begin(), notTerms.end(), st.top()));
			st.pop();

			string rule = ll_table[row][col];
			if (rule == "-1")
			{
				cerr << "No production found in parse table\n";
				return 1;
			}
			for (auto ch = rule.rbegin(); ch != rule.rend(); ++ch)
			{
				st.push(*ch);
			}

			output_state(st, input);
		}
	}

	if (st.empty())
		cout << "Success\n";
	else
		cout << "Input string doesn\'t belong to grammar\n";

	system("pause");
	return 0;
}