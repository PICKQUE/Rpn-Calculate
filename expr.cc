#include "expr.h"
Expr::Expr(std::string s, Node *head) : s{ s }, head{ head } {}

Expr::Expr(const Expr& a){
	head=a.head;
	s=a.s;
}
Expr::~Expr() {
	delete head;
}

std::string Expr::unsettedVal() {
	std::string s = head->print();
	std::stringstream ss;

	bool all_space = true;
	std::vector<std::string> temp;
	std::string strtem;
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] == ' ' || i == s.size() - 1) {
			if (s[i] != ' '&&i == s.size() - 1) {
				strtem.push_back(s[i]);
			}
			temp.push_back(strtem);
			strtem.clear();
			continue;
		}
		strtem.push_back(s[i]);
	}
	for (auto str : temp) {
		for (size_t i = 0; i < str.size(); i++) {
			if (str[i] == '-'&&str.size() == 2 && isalpha(str[1])) {
				all_space = false;
				ss << s[i + 1];
				break;
			}
			if (str.size() == 9&&find_if()) {
				ss << '-';
				ss << 'x';
				all_space = false;
				break;
			}
			if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') && str.size() > 1 && isalpha(str[1])) {
				all_space = false;
				ss << str[i++];
				while (i < str.size() && isalpha(str[i])) {
					ss << str[i++];
				}
				break;
			}
			else if (isalpha(str[i])) {
				all_space = false;
				ss << str[i];
				break;
			}
		}
		if (!all_space)break;
	}
	if (!all_space)return ss.str();
	else return "";
}


void ::Expr::setHead(Node *root) {
	if (head == nullptr) {
		this->head = root;
	}

}

Node* Expr::get_head(){
	return head;
}
std::string Expr::getInfix() {
	return s;
}


void Expr::update_infix(std::string infix) {
	s = infix;
}

int Expr::eval() {
	return head->eval();
}

std::string Expr::print() {
	std::string s = head->print();
	update_infix(s);
	return s;
}

void Expr::set(std::string target, int n) {
	head->set(target, n);
}

void Expr::unset(std::string target) {
	head->unset(target);
}



std::istream &operator>>(std::istream &in, Expr *&e) {

	std::vector<std::string> da_infix;

	std::vector<Node*> da_node;

	std::string s;

	while (in >> s) {
		std::istringstream ss(s);
		int n;
		if (ss >> n) {

			long_int *n1 = new long_int{ s };
			da_node.emplace_back(n1);
			da_infix.emplace_back(s);


		}
		else if (s == "NEG" || s == "ABS") {
			 
				Node *n1 = da_node.at(da_node.size()-1);
				da_node.erase(da_node.begin()+da_node.size()-1);
				uniaryNode *n3= new uniaryNode{ s, n1 };
			
			
			da_node.emplace_back(n3);
			if (s == "NEG") {
				std::string c = da_infix.at(0);
				da_infix.erase(da_infix.begin());
				da_infix.emplace_back("-" + c );

			}
			else if (s == "ABS") {
				std::string c = da_infix.at(da_infix.size()-1);
				da_infix.erase(da_infix.begin()+da_infix.size()-1);
				da_infix.emplace_back("|" + c + "|");
				
			}
		}
		else if (s == "+" || s == "-" || s == "*" || s == "/") {
			
			std::string c = da_infix.at(0);
			da_infix.erase(da_infix.begin());
			std::string d = da_infix.at(0);
			da_infix.erase(da_infix.begin());
			da_infix.emplace_back("(" + c + " " + s + " " + d + ")");
			
			if (da_node.size() > 2) {
				Node *n1 = da_node.at(1);
				da_node.erase(da_node.begin()+1);
				Node *n2 = da_node.at(1);
				da_node.erase(da_node.begin()+1);
				binaryNode *n3 = new binaryNode{ s, n1, n2 };
				da_node.emplace_back(n3);
			}
			else {
				Node *n1 = da_node.at(0);
				da_node.erase(da_node.begin());
				Node *n2 = da_node.at(0);
				da_node.erase(da_node.begin());
				binaryNode *n3 = new binaryNode{ s, n1, n2 };
				da_node.emplace_back(n3);
			}

		}
		else if (s == "done") {

			e->update_infix(da_infix.at(0));
			e->setHead(da_node.at(0));

			da_node.erase(da_node.begin());

			std::cout << e->print() << std::endl;


			da_infix.erase(da_infix.begin());
			break;

		}
		else {
			variable *n1 = new variable{ s };
			da_node.emplace_back(n1);
			da_infix.emplace_back(s);

		}
	}
	return in;
}