#pragma once

#include <iostream>
#include <fstream>
using namespace std;



template <typename T> class List {
	class Node {
	public:
		T value;
		Node* prev;
		Node* next;
		Node(T value = T(0), Node* prev = nullptr, Node* next = nullptr) : value(value), prev(prev), next(next) {};
	};

private:
	Node* head;
	Node* tail;
public:
	List() : head(nullptr), tail(nullptr) {};

	List(const List& list) : List() {
		Node* current = list.head;
		while (current != nullptr) {
			add_to_tail(current->value);
			current = current->next;
		}
	}

	~List() {
		while (head != nullptr) {
			delete_from_head();
		}
		delete head;
		delete tail;
	};

	void add_to_head(T value) {
		Node* add_node = new Node(value);
		if (tail == nullptr) {
			tail = add_node;
		}
		else {
			add_node->next = head;
			head->prev = add_node;
		}
		head = add_node;
	}

	void add_to_tail(T value) {
		Node* add_node = new Node(value);
		if (head == nullptr) {
			head = add_node;
		}
		else {
			tail->next = add_node;
			add_node->prev = tail;
		}
		tail = add_node;
	}

	void delete_from_head() {
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
	}

	void delete_from_tail() {
		if (head == tail) {
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else {
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
	}

	void print() {
		Node* current = head;
		cout << '\n';
		while (current != nullptr) {
			cout << current->value << '\t';
			current = current->next;
		}
	}




	class Iterator {
	private:
		Node* current;
	public:
		Iterator(Node* current = nullptr) : current(current) {};

		Iterator& operator++() {
			current = current->next;
			return *this;
		}

		Iterator& operator--() {
			current = current->prev;
			return *this;
		}

		bool operator==(const Iterator& iter) {
			return current == iter.current;
		}

		bool operator!=(const Iterator& iter) {
			return current != iter.current;
		}

		T& operator*() {
			return current->value;
		}

	};


	Iterator begin() {
		return Iterator(head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}

};


enum Type_tranz {
	popovnenna,
	znatta,
	perekaz
};


class Transaction {
private:
	string date;
	double sum;
	Type_tranz type;
public:
	Transaction(string date, double sum, Type_tranz type) : date(date), sum(sum), type(type) {};

	static Transaction from_file(istream& file) {
			string type_str;
			string date;
			double sum;
			Type_tranz type;
			file >> type_str >> date >> sum;
			if (type_str == "popovnenna") {
				type = popovnenna;
			}
			else if (type_str == "znatta") {
				type = znatta;
			}
			else if (type_str == "perekaz") {
				type = perekaz;
			}
			return Transaction(date, sum, type);
	}

	void print(ostream& os) {
		string type_str;
		if (type == 0) {
			type_str = "Popovnenna";
		}
		else if (type == 1) {
			type_str = "Znatta";
		}
		else if (type == 2) {
			type_str = "Perekaz";
		}
		os << '\n'  << type_str;
		os << "\ndate: " << date;
		os << "\nsum: " << sum;
	}

	Type_tranz get_type() {
		return type;
	}
		
	double get_sum() {
		return sum;
	}

};

ostream& operator<<(ostream& os, Transaction& tr) {
	tr.print(os);
	return os;
}


double vytraty(List<Transaction> & list) {
	double suma = 0;
	for (List<Transaction>::Iterator it = list.begin(); it != list.end(); ++it) {
		if ((*it).get_type() == znatta || (*it).get_type() == perekaz) {
			suma += (*it).get_sum();
		}
	}
	return suma;
}

double nadhodjenna(List<Transaction> & list) {
	double suma = 0;
	for (List<Transaction>::Iterator it = list.begin(); it != list.end(); ++it) {
		if ((*it).get_type() == popovnenna) {
			suma += (*it).get_sum();
		}
	}
	return suma;
}

void typed_transactions(Type_tranz type, List<Transaction> list) {
	for (List<Transaction>::Iterator it = list.begin(); it != list.end(); ++it) {
		if((*it).get_type() == type){
			cout << *it;
		}
	}
}

Transaction max_transaction(List<Transaction> list) {
	Transaction max = *list.begin();
	for (List<Transaction>::Iterator it = list.begin(); it != list.end(); ++it) {
		if ((*it).get_sum() > max.get_sum()) {
			max = *it;
		}
	}
	return max;
}

List<Transaction> less_sum(double sum, List<Transaction>& list) {
	List<Transaction> new_list;
	for (List<Transaction>::Iterator it = list.begin(); it != list.end(); ++it) {
		if (sum > (*it).get_sum()) {
			new_list.add_to_tail(*it);
		}
	}
	return new_list;
}