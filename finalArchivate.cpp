#include "bibrary.hpp"

//Stractures
//{

    struct Fourest
    {
        //than will be size_t
        int freq_;
        int right_;
        int left_;
        int parents_;

        void print ()
        {
            HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);

            SetConsoleTextAttribute (hConsole, 10);
            std::cout << "freq = " << freq_ << " ";

            SetConsoleTextAttribute (hConsole, 11);
            std::cout << "right = " << right_ << " ";

            SetConsoleTextAttribute (hConsole, 12);
            std::cout << "left = " << left_ << " ";

            SetConsoleTextAttribute (hConsole, 13);
            std::cout << "parents = " << parents_ << "\n\n";

            SetConsoleTextAttribute (hConsole, 15);
        }

        bool isInteresting ()
        {
            if (freq_ == 0 && right_ == -1 && left_ == -1 && parents_ == -1) return false;
            else                                                             return true;
        }

        Fourest (): freq_ (0), right_ (-1), left_ (-1), parents_ (-1) {};
    };

//}

//Function Declaration
//{

    void read (const char* textname, std::string& text);
    void getStats (const std::string text, Fourest* tree);
    void growTree (Fourest* tree);
    char* getCode (Fourest* tree, int letter, char* code);

    void printTree (Fourest* tree);

    void writeText (const char* fileName, const std::string& text, Fourest* tree);
    void writeTablet (const char* fileName, Fourest* tree);

//}

//Main
//{

    int main (int argc, char* argv [])
    {
        assert (argc == 2);

        std::string textToArchivate;
        read (argv [1], textToArchivate);

        Fourest tree [DOUBLESIZE];

        getStats (textToArchivate, tree);
        growTree (tree);

        writeText ("archivatedText.txt", textToArchivate, tree);
        writeTablet ("Tree.txt", tree);

        getch ();
        return 0;
    }

//}

//Function
//{

    void read (const char* textName, std::string& text)
    {
        std::ifstream myfile (textName);

        if (myfile.is_open())
        {
            for (std::string line; getline (myfile,line);) text += (line + '\n');

            myfile.close();
        }

        else std::cout << "Unable to open file";

        text.push_back (0); //he warns about THE END
    }

    void getStats (const std::string text, Fourest* tree)
    {
        for (auto i = text.begin(); i != text.end(); i++)
        {
            //printf ("Stats :: i = %d\n", (unsigned char) (*i));
            tree [(unsigned char)(*i)].freq_ ++;
        }
    }

    void growTree (Fourest* tree)
    {
        int edge = DOUBLESIZE/2;

        while (true)
        {
            int min1Ind = -1;
            int min1Val = std::numeric_limits<int>::max();

            int min2Ind = -1;
            int min2Val = std::numeric_limits<int>::max();

            for (size_t i = 0; i < DOUBLESIZE; i++)
            {
                if (tree[i].freq_ > 0 && tree[i].freq_ < min1Val) // && tree[i].freq_
                {
                    min1Ind = (int) i;
                    min1Val = tree[i].freq_;
                    continue;
                }

                if (tree[i].freq_ > 0 && tree[i].freq_ < min2Val)
                {
                    min2Ind = (int) i;
                    min2Val = tree[i].freq_;
                }

            }

            if (min1Ind != -1 && min2Ind != -1)
            {
                tree [min1Ind].parents_ = edge;
                tree [min2Ind].parents_ = edge;

                tree [min1Ind].freq_ = -tree [min1Ind].freq_;
                tree [min2Ind].freq_ = -tree [min2Ind].freq_;

                tree [edge].left_ = min1Ind;
                tree [edge].right_ = min2Ind;
                tree [edge].freq_ = min1Val + min2Val;
                edge++;
            }
            else break;
        }

        tree [edge - 1].freq_ = -tree [edge - 1].freq_;
        //return edge;
        return;
    }

    void printTree (Fourest* tree)
    {
        std::cout << "start printing Tree\n-----------------\n";
        for (size_t i = 0; i < DOUBLESIZE; i++)
        {
            if (tree[i].isInteresting())
            {
                printf ("i = %d and %c\n", (int)i, (char)i);
                tree[i].print();
            }
        }
        std::cout << "-----------------\nfinish printing\n\n";
    }

    char* getCode (Fourest* tree, int letter, char* code)
    {
        char codeRev [CODELENGTH] = {};

        int i = 0;
        for (; tree [letter].parents_ != -1; ++i)
        {
            if (tree [tree [letter].parents_].left_ == letter) codeRev [i] = Direction::CLeft;

            if (tree [tree [letter].parents_].right_ == letter) codeRev [i] = Direction::CRight; //may be just else

            letter = tree [letter].parents_;
        }

        for (int j = i-1; j >= 0; j--) code [i - j - 1] = codeRev [j];
        code [i] = 0;

        return code;
    }

    void writeText (const char* fileName, const std::string& text, Fourest* tree)
    {
        WriteBit myfile (fileName);
        char code [CODELENGTH] = {};

        for (auto i = text.begin(); i != text.end(); i++)
        {
            getCode (tree, (unsigned char)*i, code);
            myfile << code;
            //printf ("letter = %c %d code = %s\n", *i, *i, code);
        }
    }

    void writeTablet (const char* fileName, Fourest* tree)
    {
        std::ofstream myfile;
        myfile.open (fileName);

        char letter [CODELENGTH] = "";

        for (size_t i = 0; i < DOUBLESIZE/2; i++)
        {
            getCode (tree, (unsigned char)i, letter);

            if (letter [0] != 0)
            {
                myfile << i << ' ' << letter << '\n';
            }
        }

        myfile.close ();
    }
//}



