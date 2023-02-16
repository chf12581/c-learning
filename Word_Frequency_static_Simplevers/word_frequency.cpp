#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<cctype>
#include<ctime>

using std::string;
using std::endl;
using std::cout;
using std::vector;
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
	vector<Record> _dict;
};

void Dictionary::show()const
{
	cout << "size of dict = " << _dict.size() << endl;
}

void Dictionary::read(const string& filename)
{
	const char* c = filename.c_str();	//ifstream�ĳ�ʼ������C����ַ���
	ifstream ifs(c);			//���ļ���
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
			size_t i = 0;	//�����ж��Ƿ���һ����������
			for (; i < word.size(); ++i)
			{
				if (isalpha(word[i]))
					continue;
				else
					break;
			}
			if (i != word.size())	//�����������ʣ�ʲô�����ø��ĺͲ���
				continue;
			else
			{
				//���������ʣ����Ƿ��ظ�
				size_t j = 0;
				for (; j < _dict.size(); ++j)
				{
					if (word == _dict[j]._word)	//�ظ��Ӵ�Ƶ
					{
						++_dict[j]._frequency;
						break;
					}
				}//�����ж��ظ�
				if(j == _dict.size())
					_dict.push_back({ word,1 });//û���ظ�����һ���´���
			}//�������ʲ���

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
	for (size_t i = 0; i < _dict.size(); ++i) //�����ʵ䣬�����ݴ�ӡ���ļ���
	{
		ofs << _dict[i]._word << "  " << _dict[i]._frequency << endl;
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
