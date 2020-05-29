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
	virtual int insert(const book) = 0; //�[�J�@�ӭ� �^�Ǧ��\(1) ����(0)
	virtual int remove(const book) = 0; //�R���@�ӭ� �^�Ǧ��\(1) ����(0)
	virtual book* get(const char* bookName) = 0;	//�d�ߤ@�ӭ� 
	//���\�^�� ���Ы���table����
	//���Ѧ^��(0)
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
	//�[�J�@�ӭ� ���\result�]��1  ����result�]��0
	void remove(const book value, int& result) {
		auto f = mapbook.find(value.bookName);
		if (f == mapbook.end()) {
			cout << "�S��� " << value.bookName << endl;
			result = 0;
		}
		else
		{
			cout << "�R�� " <<value.bookName<< endl;
			mapbook.erase(f);
			result = 1;
		}
	
	}
	//�R���@�ӭ� ���\result�]��1  ����result�]��0
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
	//�d�ߤ@�ӭ�   ���\ ����ptr����table����
	//���� ����ptr�]��0
};


class adapter_class :public LookUpTable, public adaptee {
	int result;
public:
	int insert(const book a) { 
		adaptee::insert(a, result);
		return result; } //TODO //�[�J�@�ӭ� �^�Ǧ��\(1) ����(0)
	int remove(const book a) {
		adaptee::remove(a, result);
		return result;
	} //TODO //�R���@�ӭ� �^�Ǧ��\(1) ����(0)
	book* get(const char* bookName) {\
		book* ptr;
	     adaptee::get(bookName, ptr);
		return ptr; } //TODO //�d�ߤ@�ӭ� 
	//���\�^�� ���Ы���table����
	//���Ѧ^��(0)

};


class adapter_object :public LookUpTable {
private:
	adaptee ad;
	int result;
public:
	int insert(const book a) { 
		ad.insert(a, result);
		return result; } //TODO //�[�J�@�ӭ� �^�Ǧ��\(1) ����(0)
	int remove(const book a) { 
		ad.remove(a, result);
		return result; } //TODO //�R���@�ӭ� �^�Ǧ��\(1) ����(0)
	book* get(const char* bookName) { 
		book* ptr;
		ad.get(bookName, ptr);
		return ptr; } //TODO //�d�ߤ@�ӭ� 
	//���\�^�� ���Ы���table����
	//���Ѧ^��(0)

};

void run_LookupTable(LookUpTable* ptr) {
	cout << "Test LookupTable " << endl;
	//insert 
	cout << "Test insert" << endl;
	book val("��q���ǿ��ѧ޳N�G����ABBYY FineReader 11 OCR", "�����q", 371);
	cout << ptr->insert(val) << endl;	//�^�Ǧ��\(1)  
	val.assign("VISUAL FORTRAN�{���]�p�P�}�o", "�i�űj�B���E��", 400);
	cout << ptr->insert(val) << endl;	//�^�Ǧ��\(1)  
	val.assign("�{���]�p�Шϥ�C++", "���خx", 420);
	cout << ptr->insert(val) << endl;	//�^�Ǧ��\(1) 

	val.assign("VISUAL FORTRAN�{���]�p�P�}�o", "�i�űj�B���E��", 400);
	cout << ptr->insert(val) << endl;	//�^�ǥ���(0) 
	val.assign("�{���]�p�Шϥ�C++", "���خx", 420);
	cout << ptr->insert(val) << endl;	//�^�ǥ���(0) 

//remove 
	cout << endl << "Test remove" << endl;
	val.assign("VISUAL FORTRAN�{���]�p�P�}�o", "�i�űj�B���E��", 400);
	cout << ptr->remove(val) << endl;	//�^�Ǧ��\(1)  
	cout << ptr->remove(val) << endl;	//�^�ǥ���(0) 

//get 
	cout << endl << "Test get" << endl;
	
	cout << ptr->get("��q���ǿ��ѧ޳N�G����ABBYY FineReader 11 OCR") << endl;	//�^�Ǧ��\(1) 
	cout << ptr->get("VISUAL FORTRAN�{���]�p�P�}�o") << endl;	//�^�ǥ���(0)
	cout << ptr->get("�{���]�p�Шϥ�C++") << endl;	//�^�Ǧ��\(1)  
}

void testMap()
{
	map<string, book> mapbook;		//key:string value:book
	cout << "Test Map" << endl;

	//insert: ���J����
	book val("��q���ǿ��ѧ޳N�G����ABBYY FineReader 11 OCR", "�����q", 371);
	mapbook.insert(pair<string, book>("��q���ǿ��ѧ޳N�G����ABBYY FineReader 11 OCR", val));

	val.assign("VISUAL FORTRAN�{���]�p�P�}�o", "�i�űj�B���E��", 400);
	mapbook.insert(pair<string, book>("VISUAL FORTRAN�{���]�p�P�}�o", val));

	val.assign("�{���]�p�Шϥ�C++", "���خx", 420);
	mapbook.insert(pair<string, book>("�{���]�p�Шϥ�C++", val));

	for (auto it = mapbook.begin(); it != mapbook.end(); it++)
		cout << "key:" << it->first << ' ' << it->second << endl;

	//find 
	auto f = mapbook.find("VISUAL FORTRAN�{���]�p�P�}�o");
	if (f == mapbook.end())
		cout << "�S��� VISUAL FORTRAN�{���]�p�P�}�o" << endl;
	else
		cout << "��� VISUAL FORTRAN�{���]�p�P�}�o" << endl;

	f = mapbook.find("VISUAL FORTRAN");
	if (f == mapbook.end())
		cout << "�S��� VISUAL FORTRAN" << endl;
	else
		cout << "��� VISUAL FORTRAN" << endl;

	//�R������ find and erase the element
	f = mapbook.find("VISUAL FORTRAN�{���]�p�P�}�o");
	if (f == mapbook.end())
		cout << "�S��� VISUAL FORTRAN�{���]�p�P�}�o" << endl;
	else
	{
		cout << "�R�� VISUAL FORTRAN�{���]�p�P�}�o" << endl;
		mapbook.erase(f);
	}

	f = mapbook.find("VISUAL FORTRAN�{���]�p�P�}�o");
	if (f == mapbook.end())
		cout << "�S��� VISUAL FORTRAN�{���]�p�P�}�o" << endl;
	else
		cout << "��� VISUAL FORTRAN�{���]�p�P�}�o" << endl;

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