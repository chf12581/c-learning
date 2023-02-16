#include<iostream>
#include<string>
#include<map>
#include<fstream>
#include<sstream>
#include<cctype>
#include<ctime>

using std::string;
using std::endl;
using std::cout;
using std::map;
using std::ifstream;
using std::ofstream;

struct Record
{
	string _word;
	int _frequency;
};

class Dictionary
{
public:
	Dictionary() {};
	~Dictionary() {};
	void read(const string& filename);	//���ļ�����ȡ
	void store(const string& filename);	//����ȡ����洢��Ŀ���ļ�
	void show() const;
private:
	map <string,int> _dict;
    bool isword(string &word);
};

bool Dictionary::isword(string& word)
{
	//�����ж��Ƿ���һ����������
   for (size_t i=0; i < word.size(); ++i)
   {
   	if (!isalpha(word[i]))
   		return false;
   }
   return true;
}

void Dictionary::show()const
{
	cout << "size of dict = " << _dict.size() << endl;
}

void Dictionary::read(const string& filename)
{
	ifstream ifs(filename.c_str());			//���ļ���
	if (!ifs)	//�ļ���ʧ��
	{
		std::cerr << " file opening error! " << endl;
		return;
	}//�ж��ļ��򿪳ɹ����

	string line;	//�����ݴ�һ��
	while (getline(ifs, line))	//��ȡifs�е�һ�е�line
	{
		std::istringstream iss(line);	//��ǡ���ĸ�ʽת�����ַ���
		string word;
		while (iss >> word) //istringstreamĬ���Կո���Ϊ�ָ�����ÿ����һ������
		{
			if (isword(word))
                ++_dict[word]; //�������ʲ���
		}//ÿ����һ���е�һ������
	}//ÿ�ζ�ȡ�ļ��е�һ��
	ifs.close();	//�ر��ļ�

}//read(const string &filename)


void Dictionary::store(const string& filename)
{
	ofstream ofs(filename.c_str());	//������ļ�
	if (!ofs)
	{
		std::cerr << "ofs opening error! " << endl;
		return;
	}
	for (auto item:_dict )//�����ʵ䣬�����ݴ�ӡ���ļ���
	{
        ofs << item.first << " "<< item.second<<endl;
	}
	ofs.close();
	
}


void test()
{
	Dictionary dil;
    cout<<"before reading......"<<endl;
    time_t read_beg = time(NULL);
	dil.read("The_Holy_Bible.txt");
    time_t read_end = time(NULL);
    cout<<"finish reading......"<<endl;
    cout<<"total "<<(read_end - read_beg)<<"s"<<endl;
   
    cout<<endl;
	dil.show();
    cout<<endl;

	dil.store("Dictionary of The_Holy_Bible.txt");
}

int main(void)
{
	test();
	return 0;
}
