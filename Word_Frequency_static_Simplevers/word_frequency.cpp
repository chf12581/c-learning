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
	void read(const string& filename);	//打开文件并读取
	void store(const string& filename);	//将读取结果存储到目标文件
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
	const char* c = filename.c_str();	//ifstream的初始化接收C风格字符串
	ifstream ifs(c);			//打开文件流
	if (!ifs)	//文件打开失败
	{
		std::cerr << " file opening error! " << endl;
		return;
	}//判断文件打开成功与否

	string line;	//用于暂存一行
	while (getline(ifs, line))	//读取ifs中的一行到line
	{
		std::istringstream iss(line);	//以恰当的格式转换成字符串
		string word;
		while (iss >> word) //istringstream默认以空格作为分隔符，每次拿一个单词
		{
			size_t i = 0;	//用于判断是否是一个正常单词
			for (; i < word.size(); ++i)
			{
				if (isalpha(word[i]))
					continue;
				else
					break;
			}
			if (i != word.size())	//不是正常单词，什么都不用更改和操作
				continue;
			else
			{
				//是正常单词，看是否重复
				size_t j = 0;
				for (; j < _dict.size(); ++j)
				{
					if (word == _dict[j]._word)	//重复加词频
					{
						++_dict[j]._frequency;
						break;
					}
				}//遍历判断重复
				if(j == _dict.size())
					_dict.push_back({ word,1 });//没有重复插入一个新词条
			}//正常单词操作

		}//每次拿一行中的一个单词
	}//每次读取文件中的一行

	ifs.close();	//关闭文件

}//read(const string &filename)


void Dictionary::store(const string& filename)
{
	ofstream ofs(filename.c_str());	//打开输出文件
	if (!ofs)
	{
		std::cerr << "ofs opening error! " << endl;
		return;
	}
	for (size_t i = 0; i < _dict.size(); ++i) //遍历词典，将内容打印到文件中
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
