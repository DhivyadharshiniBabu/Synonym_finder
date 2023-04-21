#include <iostream>
#include<cstring>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

const int SIZE = 26;

// trie node
struct TrieNode
{
	struct TrieNode *child[SIZE];
	string word;
    string synonym1;
    string synonym2;
    string pronounce;
	bool isEndOfWord;       // isEndOfWord is true if the node represents
	// end of a word
};

class Trie
{
    struct TrieNode *root = new TrieNode;

public:

    struct TrieNode * getNode();
    int insert(string ,string ,string,string );
    bool search(string );
    void display(string );
    void get_synonym1(string word);
    void get_synonym2(string word);
    void get_pronounce(string word);
    bool islastnode(struct TrieNode *);
};

// Returns new trie node (initialized to NULLs)
struct TrieNode * Trie::getNode(void)
{
	struct TrieNode *N = new TrieNode;
	N->isEndOfWord = false;
	for (int i = 0; i < SIZE; i++)
    {
        N->child[i] = NULL;
    }
	return N;
}

bool Trie :: search(string word)
{
    struct TrieNode * temp = root;

    for(int i = 0 ; i < word.length() ; i++)
    {
        int ind = word[i] - 'a';
        if(temp -> child[ind] == NULL)
        {
            return false;
        }
        temp = temp -> child[ind];
    }
    return (temp -> isEndOfWord);
}

bool Trie :: islastnode(struct TrieNode * root)
{
    for(int i = 0 ; i < SIZE ; i++)
    {
        if(root -> child[i])
        {
            return 0;

        }
    }
    return 1;
}

void Trie :: get_synonym1(string word)
{
    if(search(word))
    {
       struct TrieNode * temp = root;

        for(int i = 0 ; i < word.length() ; i++)
        {
            int ind = word[i] - 'a';
            temp = temp -> child[ind];
        }

        cout << endl;
        cout << "\tSynonym1 : " << temp -> synonym1 << endl;
    }

}
void Trie :: get_synonym2(string word)
{
    if(search(word))
    {
       struct TrieNode * temp = root;

        for(int i = 0 ; i < word.length() ; i++)
        {
            int ind = word[i] - 'a';
            temp = temp -> child[ind];
        }
        cout << endl;
        cout << "\tSynonym2 : " << temp -> synonym2 << endl;
    }

}
void Trie :: get_pronounce(string word)
{
    if(search(word))
    {
       struct TrieNode * temp = root;

        for(int i = 0 ; i < word.length() ; i++)
        {
            int ind = word[i] - 'a';
            temp = temp -> child[ind];
        }
        cout << endl;
        cout << "\tProunciation: " << temp -> pronounce << endl;
    }
}

void Trie :: display(string word)
{
    if(search(word))
    {
       struct TrieNode * temp = root;

        for(int i = 0 ; i < word.length() ; i++)
        {
            int id = word[i] - 'a';
            temp = temp -> child[id];
        }

        cout << endl;
        cout << "\tWord         : " << word <<endl;
        cout << "\tSynonym1     : " << temp -> synonym1 << endl;
        cout << "\tSynonym2     : " << temp -> synonym2 << endl;
        cout << "\tProunciation : " << temp -> pronounce << endl;
    }
    else
    {
        cout << "Word not found" << endl;
    }
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
int Trie::insert(string key, string sy1,string sy2,string pro)
{
	struct TrieNode *ptr= root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = (key[i] - 'a');
		if (ptr->child[index] == NULL)
			ptr->child[index] = getNode();

		ptr = ptr->child[index];
	}
    ptr-> synonym1 = sy1;
    ptr-> synonym2 = sy2;
    ptr-> pronounce = pro;
	// mark last node as leaf
	ptr->isEndOfWord = true;
	return 0;
}

int main()
{
    int ch;
    string inp_word, inp_synm1, inp_synm2,inp_pro;
    Trie T;
    string temp ;
    ifstream f("Synonyms.csv");
    string line;
    string word[4];


    if(!f)
    {
       cerr<<endl<<"ERROR!!"<<"  The file SYNONYMS.csv can not be opened";
    }

    while(f)
    {
        int i = 0;
        temp = '\0';

        getline(f,line);

        for(int j = 0 ; j < line.length() ; j++ )
        {
            if(line[j] != ',')
            {
                temp = temp + line[j];
            }
            else
            {
                string w;

                for(int k = 0 ; k < temp.length();k++)
                {
                    if(temp[k] != '\0')
                    {
                        w = w + temp[k];
                    }
                }

                word[i] = w;
                i++;
                temp = '\0';
            }
        }

        T.insert(word[0],word[1],word[2],word[3]);
    }
    f.close();
    system("cls");
    system("color 0B0");
    do
    {
        cout<<endl;
        cout<<endl<<setw(50)<<"Welcome to our Synonym finder!";
        cout<<endl<<setw(35)<<"MENU";
        cout<<endl<<setw(35)<<"1. Synonyms.";
        cout<<endl<<setw(33)<<"2. Search.";
        cout<<endl<<setw(39)<<"3. Add new word.";
        cout<<endl<<setw(43)<<"4. Display all word.";
        cout<<endl<<setw(31)<<"5. Exit.";
        cout<<endl<<"Enter the choice:";
        cin>>ch;
        switch(ch)
        {
            case 1:
                {
                    system("cls");
                    system("color 00F");
                    fflush(stdin);
                    cout<<endl<<"Enter the word to get its synonyms and Pronounciation:";
                    cin>>inp_word;
                    T.get_synonym1(inp_word);
                    T.get_synonym2(inp_word);
                    T.get_pronounce(inp_word);
                }
                break;

            case 2:
                 {
                     system("cls");
                     system("color 0E0");
                    fflush(stdin);
                    cout<<endl<<"Enter the word you need to search:";
                    getline(cin, inp_word, '\n');
                        if(T.search(inp_word))
                        {
                            cout << "\n\n\tYes, The Word is present in the dictionary !" << endl;
                            T.display(inp_word);
                        }
                        else
                            cout<<"\n\t\tWord not found"<<endl;
                 }
                 break;

            case 3:
                {
                    system("cls");
                    system("color 0DF");
                    fflush(stdin);
                    cout<<endl;
                    cout << "\n\n\tEnter the following : " << endl;
                    cout << "\n\tWord : ";
                    getline(cin, inp_word, '\n');

                    if(!T.search(inp_word))
                    {
                    fflush(stdin);
                    cout << "\tSynonym 1: ";
                    getline(cin, inp_synm1, '\n');

                    for(int i = 0 ; i < inp_synm1.length() ; i++)
                    {
                        inp_synm1[i] = tolower(inp_synm1[i]);
                    }

                    fflush(stdin);
                    cout << "\tSynonym 2: ";
                    getline(cin, inp_synm2, '\n');

                    fflush(stdin);
                    cout << "\tPronounciation: ";
                    getline(cin, inp_pro, '\n');
                    ofstream fout("Synonyms.csv",ios :: app);

                        fout << inp_word << ',' << inp_synm1 << ','<< inp_synm2 << ',' << inp_pro << ',' <<' ';
                        fout << endl;
                        T.insert(inp_word,inp_synm1,inp_synm2,inp_pro);
                    }

                    else
                    {
                        cout<<"\n\n\tThe Word is already added in the dictionary !"<<endl;
                    }
                }
                break;

            case 4:
                {
                    system("cls");
                    system("color 08F");
                    cout<<endl;
                    int l = 0;
                    string temp ;
                    ifstream fin("Synonyms.csv");
                    string line;
                    string arr[4];

                    while(getline(fin,line))
                    {
                        l++;
                        int i = 0;
                        temp = '\0';

                        for(int j = 0 ; j < line.length() ; j++ )
                        {
                            if(line[j] != ',')
                            {
                                temp = temp + line[j];
                            }
                            else
                            {
                                string word;
                                for(int k = 0 ; k < temp.length();k++)
                                {
                                    if(temp[k] != '\0')
                                    {
                                        word = word + temp[k];
                                    }
                                }
                                arr[i] = word;
                                i++;
                                temp = '\0';
                            }
                        }
                        cout<<endl;
                        cout <<"=============================================="<< endl;
                        cout<<endl;
                        cout <<"\tWord          : " << arr[0] << endl;
                        cout <<"\tSynonyms 1    : " << arr[1] << endl;
                        cout <<"\tSynonyms 2    : " << arr[2] << endl;
                        cout <<"\tProunciation  : " << arr[3] <<endl;
                    }

                    cout << "\n\n\t\tTotal Words : " << l << endl;
                    fin.close();
                }
                break;

            case 5: exit(0);
                    break;
        }
    }while(ch==1 || ch==2 || ch==3 || ch==4 || ch==5);
}
