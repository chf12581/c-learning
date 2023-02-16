#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <ctime>


using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::set;

struct Line //用于存储行信息的结构体
{
    string _str;
    size_t _number;
};


class TextQuery
{
public:
    TextQuery(){};
    ~TextQuery(){};
    void readFile(const string &filename);  //读取文件
    void query(const string & word);//查询单词并打印结果
    
    void show() const; //测试容器是否正常接收了
    void copy() ; //测试vector接收是否正常

private:
    void preProceccLine(string &line);//对行进行预处理，全部改写为小写，非字母用空格替代


    vector<string> _line;   //每次暂存一行一遍可以输出原始行内容
    map<string , set<int>> _word2Numbers;   //单词和单词所在行
    map<string , int> _dict;
};

void TextQuery::copy()
{
    std::ofstream ofs("copy.txt");
    if(!ofs)
    {
        std::cerr<<"ofs opening error"<<endl;
    }
    for(size_t j =0;j<_line.size();++j)
    {
        ofs << _line[j]<<endl;
    }
}


void TextQuery::show()const
{
    cout<<"Totally has "<<_line.size()<<(_line.size()>1? " lines.":" line.")<<endl;
    cout<<"Dictionary has "<<_dict.size()<<" records."<<endl;
    if(_word2Numbers.size()!=_dict.size())
    {
        cout<<"Something in Dictionary is wrong!"<<endl;
    }
    else
        return;
}

void TextQuery::preProceccLine(string &line)
{
    for(auto &ch : line)    //逐字符处理
    {
        if(!isalpha(ch))    //非字母空格替代
            ch=' ';
        else if(isupper(ch))    //大写转小写
        {
            ch = tolower(ch);
        }
    }
}

void TextQuery::readFile(const string &filename)
{
    std::ifstream ifs(filename.c_str());// 打开文件
    if(!ifs)
    { 
        std::cerr<<"ifs opening error!"<<endl;
        return;
    }
    
    string str;
    size_t number=0;
    while(getline(ifs,str))   //每次读取一行
    {   
        ++number; //更新行号 
        
        _line.push_back(str);//未处理直接原始行存入

        preProceccLine(str);//预处理行内容

        std::istringstream iss(str);
        string word;
        while(iss >> word)
        {
            //统计单词与词频
            ++_dict[word];
            //将单词所在行记录下来
            _word2Numbers[word].insert(number);
        }
    }

    ifs.close();
}

void TextQuery::query(const string &word)
{
    cout << word << " occurs "<<_dict[word]<<(_dict[word]>1?" times. ": "time. ")<<endl;//打印单词总共出现的次数，保存在_dict中

    auto lines = _word2Numbers[word];   //找到该单词所出现的行号set组
    for(auto line:lines)    //遍历这些原始行并打印
    {
        cout<<"(line "<<line<<") : "<<_line[line-1]<<endl;
    }


}


bool isword(string &word)
{
    for(size_t i=1;i<word.size();++i )
    {
        if(!isalpha(word[i]))
            return false;
    }
    return true;
}

void test()
{
    TextQuery text;
    cout<<endl;
    cout<<"before reading ......"<<endl;
    time_t beg_read = time(NULL);
    text.readFile("china_daily.txt");
    time_t end_read = time(NULL);
    cout<<"finish reading ......"<<endl;
    cout<<"It has been "<<(end_read-beg_read)<<"s."<<endl;
    //测试
    text.show();
    text.copy();
    //
    cout<<endl;
    
    string word;
    while(1)
    {   cout<<"Please enter a word or enter other character to exit:  "<<endl;

        if(cin>>word)
        {
            if(!isalpha(word[1]))
                break;
            else if(isword(word))
            {
                cout<<"finding word: "<<word<<"......"<<endl;
                text.query(word);
                continue;
            } 
            else
            {
                std::cerr<<"You have entered a comlicated element! Please renter a word. "<<endl;
                continue;
            }
        }

    }//while

    cout<<"Thank you for using!"<<endl;
}

int main()
{
    test();
    return 0;
}

