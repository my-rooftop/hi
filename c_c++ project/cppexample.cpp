#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <typeinfo>
#include <bitset>
#include <cctype>
using namespace std;
//?????? ???? ????????? ???????

string hex_to_dec(int x);
string binary_inst_R_op(string s);
string binary_inst(vector<string> s, vector<string> la);
string binary_inst_R_funct(string s);
string binary_inst_I_op(string s);
string binary_inst_J_op(string s);
void data_detect(vector<vector<string>> &s, int x, int y, vector<string> &w_ad, vector<string> &w_d, vector<string> &lb, vector<string> &lba);
void text_detect(vector<vector<string>> &s, int x,vector<string> &i_adds, vector<string> &i_b, vector<string> &lb, vector<string> &lba);
void text_detect_exe(vector<vector<string>> &s, int x,vector<string> &i_adds, vector<string> &i_b, vector<string> &lb, vector<string> &lba);

void inst_lb_change(vector<string> &s, vector<string> lb, vector<string> lb_ad);
int main(void)
{   
    int locate_data;
    int locate_text;
    string File_name;
    string str;
    ifstream readFile;
    vector<string> File_in_vector;
    vector<vector<string>> split_vector_wordbyword_1;
    vector<string> split_vector_wordbyword_2;
    vector<char> split_vector_wordbyword_3;
    vector<string> label;
    vector<string> label_address;
    vector<string> word_directives;
    vector<string> word_address;
    vector<string> instruction_address;
    vector<string> instruction_binary;
    // cout << "\"sample.s\" ?? ???????????" <<endl;
    // cin >> File_name;
    vector<char> save_binary;

    cout<<"part 0. finish"<<endl;
    string filePath="sample2.s";
    // readFile.open(File_name);
    ifstream openFile(filePath.data());
    if (openFile.is_open())
    {
        while (!openFile.eof())
        {
            getline(openFile, str);
            if(str.length()!=0)
            {
                File_in_vector.push_back(str);
            }
        }//????? ?占쏙옙???? File_in_vector?? ????? ??????
        
        for (int i=0; i<File_in_vector.size();i++)
        {
            cout << File_in_vector[i] << endl;
        }
        openFile.close();

    }
    cout<<"part 1. finish"<<endl;
    for (int i=0; i<=(File_in_vector.size()-1); i++)
    {
        for (int j=0; j<(File_in_vector[i].length()); j++)
        {
            if (File_in_vector[i][j]!=' ')
            {
                split_vector_wordbyword_3.push_back(File_in_vector[i][j]);
                if (j==(File_in_vector[i].length()-1))
                {
                    string s(split_vector_wordbyword_3.begin(), split_vector_wordbyword_3.end());
                    split_vector_wordbyword_2.push_back(s);
                    split_vector_wordbyword_3.clear();
                }
            }   
            else
            {
                if (split_vector_wordbyword_3.size() != 0 )
                {
                    string s(split_vector_wordbyword_3.begin(), split_vector_wordbyword_3.end());
                    split_vector_wordbyword_2.push_back(s);
                    split_vector_wordbyword_3.clear();
                }
            }  
        }
        split_vector_wordbyword_1.push_back(split_vector_wordbyword_2);
        split_vector_wordbyword_2.clear();

    }
    // cout<<"part 2. finish"<<endl;
    // for (int r=0; r<split_vector_wordbyword_1.size(); r++)
    // {
    //     for (int t=0; t<split_vector_wordbyword_1[r].size(); t++)
    //     {
    //         cout << "split_vector_wordbyword1 [" << r << "]" << "[" << t << "]" << split_vector_wordbyword_1[r][t] << endl;
    //     }   
    // }
    for (int i=0; i<split_vector_wordbyword_1.size(); i++)
    {
        for (int t=0; t<split_vector_wordbyword_1[i].size(); t++)
        {
            if(split_vector_wordbyword_1[i][t]==".data")
            {
                locate_data=i;//.data가 나타났을때 수행할 코드
            }
            else if(split_vector_wordbyword_1[i][t]==".text")
            {
                locate_text=i;//.text가 나타났을때 수행할 코드
            }
        }
    }
    
    // cout<<split_vector_wordbyword_1[9].size()<<endl;
    data_detect(split_vector_wordbyword_1, locate_data, locate_text, word_address, word_directives, label, label_address);
    cout<<"passpoint_here"<<endl;
    text_detect(split_vector_wordbyword_1, locate_text, instruction_address, instruction_binary, label, label_address);
    cout<<"part 2. finish"<<endl;
    text_detect_exe(split_vector_wordbyword_1, locate_text, instruction_address, instruction_binary, label, label_address);
    cout<<"part 3. finish"<<endl;
    // for (int r=0; r<split_vector_wordbyword_1.size(); r++)
    // {
    //     for (int t=0; t<split_vector_wordbyword_1[r].size(); t++)
    //     {
    //         cout << "split_vector_wordbyword1 [" << r << "]" << "[" << t << "]" << split_vector_wordbyword_1[r][t] << endl;
    //     }   
    // }
    cout<<"워드파트"<<endl;
    for(int i=0; i<word_directives.size(); i++)
    {
        cout<<word_directives[i]<<endl;
        cout<<word_address[i]<<endl;   
    }
    cout<<"라벨파트"<<endl;
    for(int i=0; i<label.size(); i++)
    {
        cout<<label[i]<<endl;
        cout<<label_address[i]<<endl;   
    }
    cout<<"바이너리파트"<<endl;
    for(int i=0; i<instruction_binary.size(); i++)
    {
        cout<<instruction_binary[i]<<endl;
        cout<<instruction_address[i]<<endl;   
    }



    // text_detect(split_vector_wordbyword_1, locate_text, label, label_address, instruction_address, instruction_binary);
    // cout<<instruction_binary[0]<<label[3]<<endl;
    
    // cout<<split_vector_wordbyword_2[4]<<endl;
    // cout<<split_vector_wordbyword_2[5]<<endl;
    // cout<<split_vector_wordbyword_2[6]<<endl;

    return 0;

}

string binary_inst_R_op(string s)
{
    if (s=="addu")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="and")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="jr")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="nor")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="or")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="sltu")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="sll")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="srl")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="subu")
    {
        return bitset<6>(0).to_string();
    }//R format
}

string binary_inst_R_funct(string s)
{
    if (s=="addu")
    {  
        string sixth = "0x21";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="and")
    {
        string sixth = "0x24";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="jr")
    {
        string tenth = "8";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="nor")
    {
        string sixth = "0x27";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="or")
    {
        string sixth = "0x25";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="sltu")
    {
        string sixth = "0x2b";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="sll")
    {
        string tenth = "0";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="srl")
    {
        string tenth = "2";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="subu")
    {
        string sixth = "0x23";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }//R format
    else
    {
        return "No anything";
    }

}


//R 포맷의 인스트럭션 바이너리화 함수//모든 경우에 대해서 16진수 읽어오도록 고치자.
string binary_inst(vector<string> s, vector<string> la) // la추가하자//jformat 고치기
{
       
    string output;
    string b;
    if (s[0]=="addu"||s[0]=="and"||s[0]=="nor"||s[0]=="or"||s[0]=="sltu"||s[0]=="subu")
    {
        //이 함수의 계산하는 순서와 방식을 코드에 담아야함
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16진수를 먼저 찾는 코드
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)//분류할때 숫자만 뽑는게 아니라 0x분류, 가로에따른 분류 진행해야됨
                {
                    s[i].erase(j,1);
                    j--;
                }
                //깔끔하게 숫자만 출력하도록 하는 코드 str에 있을것으로 추정
            }
            int num = atoi(s[i].c_str());//string을 int로
            s[i]=bitset<5>(num).to_string();
            //숫자를 2진으로 바꾸는 코드
        }
        //리턴 32bit binarycode or 전부 더한다음 16진수... 이거는 더 고민해보기, binary까지만 구현해보자 일단
        
        b=binary_inst_R_funct(s[0]);
        s[0]=binary_inst_R_op(s[0]);
        output.append(s[0]);
        output.append(s[2]);
        output.append(s[3]);
        output.append(s[1]);
        output.append("00000");
        output.append(b);

        return output;
    }
    else if (s[0]=="sll")
    {
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16진수를 먼저 찾는 코드
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //깔끔하게 숫자만 출력하도록 하는 코드 str에 있을것으로 추정
            }
            int num = atoi(s[i].c_str());//string을 int로
            s[i]=bitset<5>(num).to_string();
            //숫자를 2진으로 바꾸는 코드
        }
        output.append(binary_inst_R_op(s[0]));
        output.append("00000");
        output.append(s[2]);
        output.append(s[1]);
        output.append(s[3]);
        output.append("000000");
        return output;
    }
    else if (s[0]=="srl")
    {
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16진수를 먼저 찾는 코드
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //깔끔하게 숫자만 출력하도록 하는 코드 str에 있을것으로 추정
            }
            int num = atoi(s[i].c_str());//string을 int로
            s[i]=bitset<5>(num).to_string();
            //숫자를 2진으로 바꾸는 코드
        }
        output.append(binary_inst_R_op(s[0]));
        output.append("00000");
        output.append(s[2]);
        output.append(s[1]);
        output.append(s[3]);
        output.append("000010");
        return output;
    }
    else if (s[0]=="jr")
    {
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16진수를 먼저 찾는 코드
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            
            for (int j=0; j<s[i].length(); j++)
            {
                
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //깔끔하게 숫자만 출력하도록 하는 코드 str에 있을것으로 추정
            }
            int num = atoi(s[i].c_str());//string을 int로
            s[i]=bitset<5>(num).to_string();
            //숫자를 2진으로 바꾸는 코드
        }
        b=binary_inst_R_funct(s[0]);
        output.append(binary_inst_R_op(s[0]));
        output.append(s[1]);
        output.append("000000000000000");
        output.append(b);
        return output;
    }
    else if (s[0]=="addiu"||s[0]=="andi"||s[0]=="ori"||s[0]=="sltiu")
    {
        //이 함수의 계산하는 순서와 방식을 코드에 담아야함
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16진수를 먼저 찾는 코드
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //깔끔하게 숫자만 출력하도록 하는 코드 str에 있을것으로 추정
            }
            if (i==(s.size()-1))
            {   

                int num = atoi(s[i].c_str());//string을 int로
                s[i]=bitset<16>(num).to_string();
            }
            else
            {
                int num = atoi(s[i].c_str());//string을 int로
                s[i]=bitset<5>(num).to_string();
            }
            //숫자를 2진으로 바꾸는 코드
        }
        //리턴 32bit binarycode or 전부 더한다음 16진수... 이거는 더 고민해보기, binary까지만 구현해보자 일단
        
        s[0]=binary_inst_I_op(s[0]);

        output.append(s[0]);
        output.append(s[2]);
        output.append(s[1]);
        output.append(s[3]);

        return output;
    }
    // else if (s[0]=="la")
    // {
    //     string ox="0x";
    //     string ox1="0x";
    //     vector<string> a;
    //     vector<string> b;
    //     int n;
    //     cout<<"passpoint-1"<<endl;
    //     //이 함수의 계산하는 순서와 방식을 코드에 담아야함
    //     for (int j=0; j<s[1].length(); j++)
    //     {
    //         if (isdigit(s[1][j])==0)
    //         {
    //             s[1].erase(j,1);
    //             j--;
    //         }
    //     }
        
    //     cout<<"passpoint-2"<<endl;
    //     cout<<s[2]<<endl;
    //     string front=s[2].substr(2,4);
    //     cout<<front<<endl;
    //     string last=s[2].substr(6,4);
    //     cout<<last<<endl;

    //     if(front!="0000")
    //     {
    //         cout<<"passpoint-3"<<endl;
    //         ox.append(front);
    //         s[0]="lui";
    //         s[2]=ox;

    //         a.push_back(s[0]);
    //         a.push_back(s[1]);
    //         a.push_back(s[2]);
    //         cout<<a[0]<<a[1]<<a[2]<<endl;
    //         cout<<"여기?"<<endl;
    //         binary_inst(a,la);
    //         cout<<"여기?"<<endl;
    //     }
    //     if(last!="0000")
    //     {
    //         cout<<"passpoint-4"<<endl;
    //         ox1.append(last);
    //         s[0]="ori";
    //         s[2]=ox1;
    //         b.push_back(s[0]);
    //         b.push_back(s[1]);
    //         b.push_back(s[1]);
    //         b.push_back(s[2]);
    //         cout<<b[0]<<b[1]<<b[2]<<b[3]<<endl;
    //         binary_inst(b,la);
    //     }
    // }
    else if (s[0]=="beq")
    {
        //이 함수의 계산하는 순서와 방식을 코드에 담아야함
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16진수를 먼저 찾는 코드
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //깔끔하게 숫자만 출력하도록 하는 코드 str에 있을것으로 추정
            }

            //숫자를 2진으로 바꾸는 코드
        }
        //리턴 32bit binarycode or 전부 더한다음 16진수... 이거는 더 고민해보기, binary까지만 구현해보자 일단
        int label_adds=atoi(s[3].c_str());
        string sixth = "0x00400000";
        sixth.erase(0,2);
        int _0x004 = stoi(sixth, nullptr, 16);
        string label_addres=la[la.size()-1];
        label_addres.erase(0,2);
        int ins = stoi(label_addres, nullptr, 16);
        int final_offset;
        final_offset=(label_adds-(_0x004+(ins*4+4))/4);
        s[3]=bitset<16>(final_offset).to_string();

        s[0]=binary_inst_I_op(s[0]);
        int num = atoi(s[1].c_str());
        s[1]=bitset<5>(num).to_string();
        int num1 = atoi(s[2].c_str());
        s[2]=bitset<5>(num1).to_string();
        output.append(s[0]);
        output.append(s[2]);
        output.append(s[1]);
        output.append(s[3]);

        return output;
    }
    else if (s[0]=="bne")
    {
        //이 함수의 계산하는 순서와 방식을 코드에 담아야함
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16진수를 먼저 찾는 코드
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //깔끔하게 숫자만 출력하도록 하는 코드 str에 있을것으로 추정
            }

            //숫자를 2진으로 바꾸는 코드
        }
        //리턴 32bit binarycode or 전부 더한다음 16진수... 이거는 더 고민해보기, binary까지만 구현해보자 일단
        int label_adds=atoi(s[3].c_str());
        cout<<"lookathere"<<endl;
        cout<<label_adds<<endl;
        string sixth = "0x00400000";
        sixth.erase(0,2);

        string label_addres=la[la.size()-1];
        label_addres.erase(0,2);
        int ins = stoi(label_addres, nullptr, 16);
        cout<<ins<<endl;
        int final_offset;
        final_offset=(label_adds-(ins+4))/4;
        cout<<final_offset<<endl;
        s[3]=bitset<16>(final_offset).to_string();

        s[0]=binary_inst_I_op(s[0]);
        int num = atoi(s[1].c_str());
        s[1]=bitset<5>(num).to_string();
        int num1 = atoi(s[2].c_str());
        s[2]=bitset<5>(num1).to_string();
        output.append(s[0]);
        output.append(s[1]);
        output.append(s[2]);
        output.append(s[3]);

        return output;
    }
    else if (s[0]=="lui")
    {
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16진수를 먼저 찾는 코드
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //깔끔하게 숫자만 출력하도록 하는 코드 str에 있을것으로 추정
            }
            if (i==(s.size()-1))
            {
                int num = atoi(s[i].c_str());
                s[i]=bitset<16>(num).to_string();  
            }
            else
            {
                int num = atoi(s[i].c_str());//string을 int로
                s[i]=bitset<5>(num).to_string();
            }
            //숫자를 2진으로 바꾸는 코드
        }
        output.append(binary_inst_I_op(s[0]));
        output.append("00000");
        output.append(s[1]);
        output.append(s[2]);
        return output;
    }
    else if (s[0]=="lw"||s[0]=="lb"||s[0]=="sw"||s[0]=="sb")
    {
        //이 함수의 계산하는 순서와 방식을 코드에 담아야함
        string a;
        for (int i=1; i<s.size(); i++)
        {
            if(i==(s.size()-1))//마지막에서 ()안에 있는 숫자를 추출
            {
                int j=0;
                while(s[i][j]!='(')
                {
                    a+=s[i][j];//문제있음
                    s[i][j]='*';
                    j++;
                }
            }
            if (s[i][1]=='x')//16진수를 먼저 찾는 코드
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //깔끔하게 숫자만 출력하도록 하는 코드 str에 있을것으로 추정
            }
            int num = atoi(s[i].c_str());//string을 int로
            s[i]=bitset<5>(num).to_string();
            //숫자를 2진으로 바꾸는 코드
        }
        //리턴 32bit binarycode or 전부 더한다음 16진수... 이거는 더 고민해보기, binary까지만 구현해보자 일단
        
        s[0]=binary_inst_I_op(s[0]);
        output.append(s[0]);
        output.append(s[2]);
        output.append(s[1]);
        int num = atoi(a.c_str());
        output.append(bitset<16>(num).to_string());

        return output;
    }
    else if(s[0]=="j"||s[0]=="jal")
    {
        for (int i=1; i<s.size(); i++)
        {
            // cout<<"여기는?2"<<endl;
            if (s[i][1]=='x')//16진수를 먼저 찾는 코드
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                nDec=nDec/4;
                string str1 = to_string(nDec);
                s[i]=str1;
                // cout<<s[i]<<endl;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //깔끔하게 숫자만 출력하도록 하는 코드 str에 있을것으로 추정
            }
            int num = atoi(s[i].c_str());//string을 int로
            // cout<<num<<endl;
            s[i]=bitset<26>(num).to_string();
            //숫자를 2진으로 바꾸는 코드
        }
        s[0]=binary_inst_J_op(s[0]);
        output.append(s[0]);
        output.append(s[1]);
        // cout<<output<<endl;
        return output;
    }
    else
    {
        output.append("not yet");
        return output;
    }

}

string binary_inst_I_op(string s)
{
    if (s=="addiu")
    {  
        string tenth = "9";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="andi")
    {
        string sixth = "0xc";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="beq")
    {
        string tenth = "4";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="lui")
    {
        string sixth = "0xf";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="bne")
    {
        string tenth = "5";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="lw")
    {
        string sixth = "0x23";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="lb")
    {
        string sixth = "0x20";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="ori")
    {
        string sixth = "0xd";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="sltiu")
    {
        string sixth = "0xb";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="sw")
    {
        string sixth = "0x2b";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }//R format
    else if (s=="sb")
    {
        string sixth = "0x28";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }//R format
    else
    {
        return "No anything";
    }
}

string binary_inst_J_op(string s)
{
    if (s=="jal")
    {
        string tenth = "3";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();

    }
    if (s=="j")
    {
        string tenth = "2";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
}


void data_detect(vector<vector<string>> &s, int x, int y, vector<string> &w_ad, vector<string> &w_d, vector<string> &lb, vector<string> &lba)
{
    string sixth = "0x10000000";
    sixth.erase(0,2);
    int nDec = stoi(sixth, nullptr, 16);
    int start=x+1;
    for(int i=start; i<y; i++)
    {
        if(s[i].size()==0)
        {
            
        }
        else
        {
            for(int t=0; t<s[i].size(); t++)
            {
                if (s[i][t]==".word")
                {   
                    // cout<<s[i][t+1]<<endl;
                    w_d.push_back(s[i][t+1]);
                    w_ad.push_back(hex_to_dec(nDec));
                    //int를 16진수로 변환하는 방법 알아내기
                }
            }

            int j= s[i][0].length()-1;
            if(s[i][0][j]==':')
            {   
                s[i][0].erase(j,1);
                // cout<<s[i][0]<<endl;
                lb.push_back(s[i][0]);
                // cout<<hex_to_dec(nDec)<<endl;
                lba.push_back(hex_to_dec(nDec));//[i]번째에 해당하는 word의 주소 대입하기.                 
            }
            nDec+=4; 
        } 
    }
}

void text_detect(vector<vector<string>> &s, int x,vector<string> &i_adds, vector<string> &i_b, vector<string> &lb, vector<string> &lba)
{
    string sixth = "0x00400000";
    string a;
    sixth.erase(0,2);
    int nDec = stoi(sixth, nullptr, 16);
    int start=x+1;
    for(int i=start; i<s.size(); i++)
    {

        if(s[i].size()!=0)
        {
            int j=s[i][0].size()-1;
            if(s[i][0][j]==':')
            {
                a=s[i][0];
                a.erase(j,1);
                lb.push_back(a);
                lba.push_back(hex_to_dec(nDec));
                // cout<<nDec<<endl;
            }            
        }
        if (s[i].size()==0)
        {
            nDec-=4;            
        }
        if(s[i].size()!=1)
        {
        nDec+=4;            
        }
    }
    // for (int i=start; i<s.size(); i++)
    // {
    //     int t=s[i][0].size()-1;
    //     if(s[i].size()!=1)
    //     {
    //         if(s[i][0][t]==':')
    //         {
    //             s[i].erase(s[i].begin());
    //             cout<<"passpass"<<s[i][0]<<endl;
    //         }
    //     }
    // }
    // cout<<"passpoint_here1"<<endl;
    // string sixth = "0x00400000";
    // sixth.erase(0,2);
    // int nDec = stoi(sixth, nullptr, 16);
    // int start=x+1;
    // cout<<"passpoint_here2"<<endl;
    // for (int i=start; i<(s.size()); i++)//비어있는 줄은 제외
    // {   
    //     if(s[i].size()==0)
    //     {
    //         nDec-=4;
    //     }
    //     else
    //     {
    //         cout<<"passpoint_here3"<<endl;
    //         int j= s[i][0].length()-1;
    //         if(s[i][0][j]==':')//라벨이 인식되면 라벨 정보를 벡터에 저장한다
    //         {
    //             s[i][0].erase(j,1);
    //             cout<<"passpoint_here4"<<endl;
    //             cout<<s[i][0]<<endl;
    //             cout<<nDec<<endl;
    //             lb.push_back(s[i][0]);
    //             lba.push_back(hex_to_dec(nDec));
    //         //[i]번째에 해당하는 word의 주소 대입하기.                 
    //         }
    //     nDec+=4;
    //     }
    // }
    // nDec = stoi(sixth, nullptr, 16);
    // for (int i=start; i<(s.size()); i++)//비어있는 줄은 제외
    // {   
    //     if(s[i].size()==0)
    //     {
    //         nDec-=4;
    //     }
    //     else
    //     {
    //         if(s[i].size()!=1)//라벨만 있으면 거른다.//라벨만 있을경우 주소값을 더하지 않도록 설정하자
    //         {
    //             cout<<"passpoint_instruction"<<endl;
    //             int j= s[i][0].length()-1;
    //             if(s[i][0][j]==':')
    //             {
    //                 s[i].erase(s[i].begin());
    //             }
    //             inst_lb_change(s[i], lb, lba); //바꿔준다음에
    //             i_b.push_back(binary_inst(s[i])); 
    //             i_adds.push_back(hex_to_dec(nDec));
    //         }
    //     nDec+=4;
    //     }
    // }

}

string hex_to_dec(int x)
{
	int remainder; 
	int quotient;
	int i = 1, j, temp;
	string hexadecimalNumber;
	string new_hexadecimalNumber;

	quotient = x;
	while (quotient != 0) {
		temp = quotient % 16;
		//To convert integer into character
		if (temp < 10)
		{
			temp = temp + 48;
		}
		else 
		{
			temp = temp + 55;
		}
		hexadecimalNumber.push_back(temp);
		quotient = quotient / 16;
	}

	new_hexadecimalNumber.push_back('0');
	new_hexadecimalNumber.push_back('x');
	for (int i = hexadecimalNumber.size()-1; i >= 0; i--)
	{
		hexadecimalNumber[i] = tolower(hexadecimalNumber[i]);
		new_hexadecimalNumber.push_back(hexadecimalNumber[i]);
	}
	return new_hexadecimalNumber;
} 

void inst_lb_change(vector<string> &s, vector<string> lb, vector<string> lb_ad)//인스트럭션의 label을 교체해주자
{
    // cout<<"s[i][0]"<<s[0]<<endl;
    for (int i=1; i<s.size(); i++)
    {
        for (int j=0; j<lb.size(); j++ )
        {
            if (s[i]==lb[j])
            {
                // cout<<i<<endl;
                // cout<<"here!!!!"<<s[i]<<endl;
                s[i]=lb_ad[j];
                // cout<<"here!!!!"<<s[i]<<endl;
            }
        }
    }
}

void text_detect_exe(vector<vector<string>> &s, int x,vector<string> &i_adds, vector<string> &i_b, vector<string> &lb, vector<string> &lba)
{
    cout<<"여기어때"<<endl;
    string sixth = "0x00400000";
    string a;
    sixth.erase(0,2);
    int nDec = stoi(sixth, nullptr, 16);
    int start=x+1;
    cout<<"여기어때2"<<endl;
    for (int i=start; i<s.size(); i++)
    {
        cout<<s[i][0]<<"여기어때3"<<endl;
        if(s[i].size()!=0)
        {
            cout<<"여기어때4"<<endl;
            int t=s[i][0].size()-1;
            if(s[i].size()!=1)
            {   
                cout<<"여기어때5"<<endl;
                if(s[i][0][t]==':')
                {
                    cout<<"여기어때6"<<endl;
                    cout<<s[i][0]<<endl;
                    s[i].erase(s[i].begin());
                    cout<<s[i][0]<<endl;
                } //바꿔준다음에
                inst_lb_change(s[i], lb, lba);
                // cout<<s[i][0]<<s[i][1]<<endl;
                // cout<<hex_to_dec(nDec)<<endl;
                if(s[i][0]=="la")
                {
                    string ox="0x";
                    string ox1="0x";
                    vector<string> a;
                    vector<string> b;
                    int n;
                    //이 함수의 계산하는 순서와 방식을 코드에 담아야함
                    for (int j=0; j<s[i][1].length(); j++)
                    {
                        if (isdigit(s[i][1][j])==0)
                        {
                            s[i][1].erase(j,1);
                            j--;
                        }
                    }
                    cout<<s[i][2]<<endl;
                    string front=s[i][2].substr(2,4);
                    cout<<front<<endl;
                    string last=s[i][2].substr(6,4);
                    cout<<last<<endl;

                    if(front!="0000")
                    {
                        cout<<"passpoint-3"<<endl;
                        ox.append(front);
                        s[i][0]="lui";
                        s[i][2]=ox;

                        a.push_back(s[i][0]);
                        a.push_back(s[i][1]);
                        a.push_back(s[i][2]);
                        cout<<a[0]<<a[1]<<a[2]<<endl;
                        i_adds.push_back(hex_to_dec(nDec));
                        i_b.push_back(binary_inst(a,lba));
                        nDec+=4;

                    }
                    if(last!="0000")
                    {
                        cout<<"passpoint-4"<<endl;
                        ox1.append(last);
                        s[i][0]="ori";
                        s[i][2]=ox1;
                        b.push_back(s[i][0]);
                        b.push_back(s[i][1]);
                        b.push_back(s[i][1]);
                        b.push_back(s[i][2]);
                        cout<<b[0]<<b[1]<<b[2]<<b[3]<<endl;
                        i_adds.push_back(hex_to_dec(nDec));
                        i_b.push_back(binary_inst(b,lba));
                        nDec+=4;
                    }
                }
                else
                {
                    i_adds.push_back(hex_to_dec(nDec));
                    i_b.push_back(binary_inst(s[i],lba)); 
                    nDec+=4;
                }
                // cout<<binary_inst(s[i],i_adds)<<endl;
                // nDec+=4;
            }
            else
            {
                /* code */
            }
              
        }
        else
        {
            /* code */
        }
    cout<<"여기어때7"<<endl;
    }
    cout<<"여기어때8"<<endl;
}