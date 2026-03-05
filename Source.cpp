#include "Header.h"


int main() {
	List<Transaction> transactions;
	ifstream file("Text.txt");
	if (file.is_open()) {
		for (int i = 0; i < 6; ++i) {
			transactions.add_to_tail(Transaction::from_file(file));
		}
		file.close();
	}
	transactions.print();
	cout << "\n\nVytraty: " << vytraty(transactions);
	cout << "\nNadhodj: " << nadhodjenna(transactions);

	typed_transactions(perekaz, transactions);

	Transaction max = max_transaction(transactions);
	cout << max;

	cout << "\n\n---------------------------------------\n\nless_100:";
	List<Transaction> less = less_sum(100, transactions);
	less.print();

	cout << "\n\n---------------------------------------\n\nless_0: ";
	List<Transaction> less_0 = less_sum(0, transactions);
	less_0.print();
}

