// This program demonstrates the Is A relationship
 // in inheritance.
 #include <iostream>
#include <vector>
#include <string>
#include <sstream>
 using namespace std;

 // Base class
 class Dog {
	 vector<string> tempProfits;
 public:
	 int vectorPopulator(vector<int> prices, int maxTrans) {
		 int tempProfit = 0;
		 string size;
		 size = to_string(prices.size()).length();
		 for (int i = 0; i < prices.size(); i++) {
			 //i is the day he bought and s is when he sold
			 for (int j = 0; j < prices.size(); j++) {
				 if (prices.at(i) < prices.at(j) && j > i) {
					 tempProfit = prices.at(j) - prices.at(i);
					 ostringstream oss;
					 oss <<  "B" << i << "P" << tempProfit << "S" << j;
					 tempProfits.push_back(oss.str());
				 }
			 }
		 }
		 mainAlgorithm(maxTrans);
		 return 0;
	 }

	 void mainAlgorithm(int maxTrans) {
		 int currentProfit = 0;
		 int count = 0;
		 int kCounter = 0;
		 int failSafeCounter = 0;
		 int bestTotal = 0;
		 string finalMaxProfit;
		 for (int i = 0; i < tempProfits.size(); i++) {
			 for (int j = 0; j < tempProfits.size(); j++) {
				 singleTradeProcessor(maxTrans, failSafeCounter, count, j,finalMaxProfit,bestTotal,currentProfit);
				 if (maxTrans > 1) {
					 failSafeCounter++;
					 if (failSafeCounter >= tempProfits.size()) {
						 failSafeCounter = -1;
					 }
					 //singleTradeProcessor(maxTrans, failSafeCounter, count, j);//check again before resetting the loop
					 
					 if (checkForSell((tempProfits.at(i)), getBuy(tempProfits.at(j)))) {
						 if (kCounter > maxTrans) {//means we already found the max amount of transactions(BUY/SELL) possible for the first transaction and we must change the primary transaction
							 break;
						 }
						 currentProfit = getProfit(tempProfits.at(i)) + getProfit(tempProfits.at(j));
						 ostringstream oss;//we have to create a new object every new line
						 oss << "Nice trades\t " << tempProfits.at(i) << "____" << tempProfits.at(j);
						 count = j;
						 kCounter += 2;
						 for (int z = 0; z < tempProfits.size(); z++) {//checks if there are more possible trades
							 if (checkForSell(tempProfits.at(count), getBuy(tempProfits.at(z)))) {//get everysingle buy and check if any of them are bigger then j
								 kCounter++;
								 if (kCounter > maxTrans) {
									 break;
								 }
								 oss << "____" << tempProfits.at(z);
								 currentProfit += getProfit(tempProfits.at(z));
								 count = z;//assigning previous transaction to count so we can compare the last index to a new buy
							 }
						 }
						 if (currentProfit > bestTotal) {
							 bestTotal = currentProfit;
							 finalMaxProfit = oss.str();
						 }
						 cout << oss.str();
						 kCounter = 0;
						 cout << " | Profit = " << currentProfit << endl;
					 }
				 }
			 }
		 }
		 cout << "\n\nBEST POSSIBLE STATS " << finalMaxProfit << " | " << bestTotal << endl << endl;
	 }

	 void singleTradeProcessor(int &maxTrans, int &failSafeCounter, int &count, int &j,string finalMaxProfit, int &bestTotal, int currentProfit){
		 if (maxTrans == 1 || failSafeCounter == -1) {
			 currentProfit = getProfit(tempProfits.at(j));
			 cout << "nice trade\t " << tempProfits.at(j) << " | Profit = " << getProfit(tempProfits.at(j)) << endl;
			 if (currentProfit > bestTotal) {
				 bestTotal = currentProfit;
			 }
			 count++;
			 if (count == tempProfits.size() && maxTrans == 1) {
				 cout << "\n\nBEST POSSIBLE STATS " << tempProfits.at(j) << " | " << bestTotal << endl << endl;
				 exit(0);
			 }
		 }
	 }

	 bool checkForSell(string transaction, int BuyIndex) {

		 if (findLastSellIndex(transaction) < BuyIndex) {
			 return true;
		 }
		 return false;
	 }

	 int findLastSellIndex(string transaction) {//get everything after 's'
		 int sellIndex = 0;
		 string sellIndexString = "";
		 for (int i = 0; i < transaction.length(); i++) {
			 if (transaction[i] == 'S') {
				 sellIndexString = transaction.substr(i + 1);
				 sellIndex = stoi(sellIndexString);
			 }
		 }
		 return sellIndex;
	 }

	 int getBuy(string transaction) {

		 return stoi(string(transaction.begin() + transaction.find('B') + 1, transaction.begin() + transaction.find('P')));
	 }

	 int getProfit(string transaction) {
		 int indexOfP = 0;
		 int indexOfS = 0;
		 int profit;

		 for (int i = 0; i < transaction.length(); i++) {
			 if (transaction[i] == 'P') {
				 indexOfP = i;
			 }
			 else if (transaction[i] == 'S') {
				 indexOfS = i;
			 }
		 }
		 profit = stoi(string(transaction.begin() + indexOfP + 1, transaction.begin() + indexOfS));//already does the -1 for us in indexOfS because the end ot the string is always exclusive meaning we don't include the last char
		 return profit;
	 }
	
 };

 // A SheepDog is a special type of Dog.

int main() {
	Dog asd;
	vector<int>list;
	int input;
	int maxTrans;
	cout << "enter a few numbers consisting of the daily prices by pressing space and press \"-1\" when finished : ";
	while (cin >> input) {
		if (input == -1)
			break;
		list.push_back(input);
	}
		
	cout << endl << "Enter a number of maximum transactions then press enter : ";
	cin >> maxTrans;
	asd.vectorPopulator(list,maxTrans);
 }
