#include <iostream>
#include <string>
#include <map>

using namespace std;


class book //class adaptee
{
	friend ostream& operator<<(ostream&, const book&);
	friend class adaptee;
	//friend  void run_LookupTable(LookUpTable* ptr);
private:
	string bookName;
	string authors;
	int price;
	// ...
public:
	
	book() :price(0) {}
	book(const char* b, const char* a, const int p)
		:bookName(b), authors(a), price(p) {	}
	void assign(const char* b, const char* a, const int p)
	{
		bookName = b;		authors = a;		price = p;
	}
};

ostream& operator<<(ostream& os, const book& b)
{
	os << "bookName:" << b.bookName
		<< "\tauthors:" << b.authors
		<< "\tprice:" << b.price << endl;
	return os;
}

// Target Class
class LookUpTable
{
public:
	virtual int insert(const book) = 0; //加入一個值 回傳成功(1) 失敗(0)
	virtual int remove(const book) = 0; //刪除一個值 回傳成功(1) 失敗(0)
	virtual book* get(const char* bookName) = 0;	//查詢一個值 
	//成功回傳 指標指到table的值
	//失敗回傳(0)
};

class adaptee {
private:
	map<string, book> mapbook;

	//TODO
public:
	void insert(const book value, int& result) {
		auto f = mapbook.find(value.bookName);
		if (f == mapbook.end()) {	
			result = 1;
			mapbook.insert(pair<string, book>(value.bookName, value));
		}
		else
		{
			result = 0;
		}

		
	}
	//加入一個值 成功result設成1  失敗result設成0
	void remove(const book value, int& result) {
		auto f = mapbook.find(value.bookName);
		if (f == mapbook.end()) {
			cout << "沒找到 " << value.bookName << endl;
			result = 0;
		}
		else
		{
			cout << "刪除 " <<value.bookName<< endl;
			mapbook.erase(f);
			result = 1;
		}
	
	}
	//刪除一個值 成功result設成1  失敗result設成0
	void get(const char* bookName, book*& ptr) {
		auto f = mapbook.find(bookName);
		if (f == mapbook.end()) {
			ptr = 0;
		}
		else
		{
			ptr = &(f->second);
		}

		/*for (auto it = mapbook.begin(); it != mapbook.end(); ++it) {
			if (it->second.bookName == bookName) {
				ptr = &(it->second);
				return;
			}
				
		}*/
		
			
	
	}
	//查詢一個值   成功 指標ptr指到table的值
	//失敗 指標ptr設成0
};


class adapter_class :public LookUpTable, public adaptee {
	int result;
public:
	int insert(const book a) { 
		adaptee::insert(a, result);
		return result; } //TODO //加入一個值 回傳成功(1) 失敗(0)
	int remove(const book a) {
		adaptee::remove(a, result);
		return result;
	} //TODO //刪除一個值 回傳成功(1) 失敗(0)
	book* get(const char* bookName) {\
		book* ptr;
	     adaptee::get(bookName, ptr);
		return ptr; } //TODO //查詢一個值 
	//成功回傳 指標指到table的值
	//失敗回傳(0)

};


class adapter_object :public LookUpTable {
private:
	adaptee ad;
	int result;
public:
	int insert(const book a) { 
		ad.insert(a, result);
		return result; } //TODO //加入一個值 回傳成功(1) 失敗(0)
	int remove(const book a) { 
		ad.remove(a, result);
		return result; } //TODO //刪除一個值 回傳成功(1) 失敗(0)
	book* get(const char* bookName) { 
		book* ptr;
		ad.get(bookName, ptr);
		return ptr; } //TODO //查詢一個值 
	//成功回傳 指標指到table的值
	//失敗回傳(0)

};

void run_LookupTable(LookUpTable* ptr) {
	cout << "Test LookupTable " << endl;
	//insert 
	cout << "Test insert" << endl;
	book val("精通光學辨識技術：應用ABBYY FineReader 11 OCR", "黃敦義", 371);
	cout << ptr->insert(val) << endl;	//回傳成功(1)  
	val.assign("VISUAL FORTRAN程式設計與開發", "張嘉強、陳鴻智", 400);
	cout << ptr->insert(val) << endl;	//回傳成功(1)  
	val.assign("程式設計－使用C++", "黃建庭", 420);
	cout << ptr->insert(val) << endl;	//回傳成功(1) 

	val.assign("VISUAL FORTRAN程式設計與開發", "張嘉強、陳鴻智", 400);
	cout << ptr->insert(val) << endl;	//回傳失敗(0) 
	val.assign("程式設計－使用C++", "黃建庭", 420);
	cout << ptr->insert(val) << endl;	//回傳失敗(0) 

//remove 
	cout << endl << "Test remove" << endl;
	val.assign("VISUAL FORTRAN程式設計與開發", "張嘉強、陳鴻智", 400);
	cout << ptr->remove(val) << endl;	//回傳成功(1)  
	cout << ptr->remove(val) << endl;	//回傳失敗(0) 

//get 
	cout << endl << "Test get" << endl;
	
	cout << ptr->get("精通光學辨識技術：應用ABBYY FineReader 11 OCR") << endl;	//回傳成功(1) 
	cout << ptr->get("VISUAL FORTRAN程式設計與開發") << endl;	//回傳失敗(0)
	cout << ptr->get("程式設計－使用C++") << endl;	//回傳成功(1)  
}

void testMap()
{
	map<string, book> mapbook;		//key:string value:book
	cout << "Test Map" << endl;

	//insert: 插入元素
	book val("精通光學辨識技術：應用ABBYY FineReader 11 OCR", "黃敦義", 371);
	mapbook.insert(pair<string, book>("精通光學辨識技術：應用ABBYY FineReader 11 OCR", val));

	val.assign("VISUAL FORTRAN程式設計與開發", "張嘉強、陳鴻智", 400);
	mapbook.insert(pair<string, book>("VISUAL FORTRAN程式設計與開發", val));

	val.assign("程式設計－使用C++", "黃建庭", 420);
	mapbook.insert(pair<string, book>("程式設計－使用C++", val));

	for (auto it = mapbook.begin(); it != mapbook.end(); it++)
		cout << "key:" << it->first << ' ' << it->second << endl;

	//find 
	auto f = mapbook.find("VISUAL FORTRAN程式設計與開發");
	if (f == mapbook.end())
		cout << "沒找到 VISUAL FORTRAN程式設計與開發" << endl;
	else
		cout << "找到 VISUAL FORTRAN程式設計與開發" << endl;

	f = mapbook.find("VISUAL FORTRAN");
	if (f == mapbook.end())
		cout << "沒找到 VISUAL FORTRAN" << endl;
	else
		cout << "找到 VISUAL FORTRAN" << endl;

	//刪除元素 find and erase the element
	f = mapbook.find("VISUAL FORTRAN程式設計與開發");
	if (f == mapbook.end())
		cout << "沒找到 VISUAL FORTRAN程式設計與開發" << endl;
	else
	{
		cout << "刪除 VISUAL FORTRAN程式設計與開發" << endl;
		mapbook.erase(f);
	}

	f = mapbook.find("VISUAL FORTRAN程式設計與開發");
	if (f == mapbook.end())
		cout << "沒找到 VISUAL FORTRAN程式設計與開發" << endl;
	else
		cout << "找到 VISUAL FORTRAN程式設計與開發" << endl;

	cout << endl << endl;
}

void main()
{
	testMap();
	
	cout << "\n\nTest adapter_class" << endl;
	
	
	adapter_class ac;
	
	run_LookupTable(&ac);

	cout << "\n\nTest adapter_object" << endl;
	adapter_object ao;
	run_LookupTable(&ao);
 
	system("pause");
}